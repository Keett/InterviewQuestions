#include "CalculateScore.h"

class CalculateScore : public ICalculateScore
{
public:

    /// <summary>
    /// T�m ta�lar�n katsay�s�na g�re puanlamalar�n�n hesaplanmas�n� sa�lar.
    /// </summary>
    /// <param name="chessboard">Santran� Tahtas�</param>
    std::map<std::string,double> calculateScore(std::vector<std::vector<Piece>>& chessboard) {
        
        findThreatenedCell(chessboard);

        double totalWhiteScore = 0;
        double totalBlackScore = 0;

        for (int xAxis = 0; xAxis < Chessboard::CHESSBOARD_SIZE; ++xAxis) {
            for (int yAxis = 0; yAxis < Chessboard::CHESSBOARD_SIZE; ++yAxis) {
                Piece piece = chessboard[xAxis][yAxis];
                bool is_threatened = threatenedPieces[{xAxis, yAxis}];

                if (piece.pieceType != PieceType::IDLE || piece.color != Color::IDLE) {

                    double score = calculatePieceScore(piece, is_threatened);
                    (piece.color == Color::SIYAH) ? totalBlackScore += score : totalWhiteScore += score;
                }
            }
        }
        scoreMap["WhiteScore"] = totalWhiteScore;
        scoreMap["BlackScore"] = totalBlackScore;

        return scoreMap;
    }

private:
    //DEFINATIONS
    std::map<std::pair<int, int>, bool> threatenedPieces;
    std::map<std::string, double> scoreMap;
    std::map<PieceType, int> pieceScores = {
        {PieceType::P�YON, 1},
        {PieceType::AT, 3},
        {PieceType::FIL, 3},
        {PieceType::KALE, 5},
        {PieceType::VEZIR, 9},
        {PieceType::SAH, 100}
    };

    // Inherited via ICalculateScore

    /// <summary>
    /// Santra� ta��n�n tehdit durumlar�n�n kontrol� i�in olu�turulmu� ortak logic yap�s�
    /// (Bulunan tehdit alan� santran� ta��n�n alan�n�n i�inde mi?,
    /// Santran� tahtas�nda bulunan pozisyon de�erlerinde ta� var m�?,
    /// bulunan ta� tehdit mi?)
    /// </summary>
    /// <param name="newPosX">Bulunan yeni posX de�eri</param>
    /// <param name="newPosY">Bulunan yeni posY de�eri</param>
    /// <param name="chessboard">Santran� Tahtas�</param>
    /// <param name="piece">Santran� Ta��</param>
    /// <returns>True veya False</returns>
    bool isChessboardControl(int newPosX, int newPosY, std::vector<std::vector<Piece>>& chessboard, const Piece& piece) override
    {
        if (newPosX >= 0 && newPosX < Chessboard::CHESSBOARD_SIZE &&
            newPosY >= 0 && newPosY < Chessboard::CHESSBOARD_SIZE &&
            chessboard[newPosX][newPosY].pieceType != PieceType::IDLE &&
            piece.color != chessboard[newPosX][newPosY].color) {
            return true;
        }
        return false;
    }

    /// <summary>
    /// Ta�a g�re tehdit edilen santran� ta�lar�n�n konumlar�n�n bulunmas�n� sa�lar.
    /// </summary>
    /// <param name="piece">Santran� Ta��</param>
    /// <param name="chessboard">Santran� Tahtas�</param>
    void findThreatenedCellsByPiece(const Piece& piece, std::vector<std::vector<Piece>>& chessboard) override
    {
        switch (piece.pieceType) {
        /// <summary>
        /// Piyon tehditleri
        /// Beyaz piyonlar�n yukar� y�nl� ve siyah piyonlar�n a�a�� y�nl� hareketi mevcuttur.
        /// Bu sebeple newPosX de�erleri renge g�re kontrol edilmektedir.
        /// </summary>
        /// <param name="piece">Santran� Ta��</param>
        /// <param name="chessboard">Santra� Tahtas�</param>
        case PieceType::P�YON:
        {
            int yAxisMotion[] = { -1, 1 };
            int newPosX = -1;
            int newPosY = -1;

            for (int i = 0; i < 2; ++i) {
                newPosX = (piece.color == Color::BEYAZ) ? (piece.position.posX - 1) : (piece.position.posX + 1);
                newPosY = (piece.position.posY) + yAxisMotion[i];

                if (isChessboardControl(newPosX, newPosY, chessboard, piece)) {
                    threatenedPieces[{newPosX, newPosY}] = true;
                }
            }
        }
        break;
        /// <summary>
        /// At tehditleri 
        /// L �eklinde tehdit hareketleri mevcut (2 yukar� - 1 sola, 2 yukar� - 1 sa�a, 2 sola - 1 yukar�, 2 sa�a - 1 yukar� gibi.)
        /// </summary>
        /// <param name="piece">Santran� Ta��</param>
        /// <param name="chessboard">Santra� Tahtas�</param>
        case PieceType::AT:
        {
            int xAxisMotion[] = { 2, 2, 1, 1, -1, -1, -2, -2 };
            int yAxisMotion[] = { 1, -1, 2, -2, 2, -2, 1, -1 };

            for (int i = 0; i < 8; ++i) {
                int newPosX = piece.position.posX + xAxisMotion[i];
                int newPosY = piece.position.posY + yAxisMotion[i];

                if (isChessboardControl(newPosX, newPosY, chessboard, piece)) {
                    threatenedPieces[{newPosX, newPosY}] = true;
                }
            }
        }
        break;
        /// <summary>
        /// Vezir tehditleri
        /// Vezirin �apraz ve d�z eksenli hareketi mevcuttur.
        /// Vezirin hareketi kendi grubundan ta�a kadar devam eder, kendi grubundan de�ilse tehdittir.  
        /// </summary>
        /// <param name="piece">Santran� Ta��</param>
        /// <param name="chessboard">Santran� Tahtas�</param>
        case PieceType::VEZIR:
        {
            int xAxisMotion[] = { 1, -1, 0, 0, 1, 1, -1, -1 };
            int yAxisMotion[] = { 0, 0, 1, -1, 1, -1, 1, -1 };

            for (int axis = 0; axis < 8; axis++)
            {
                for (int i = 1; piece.position.posX + xAxisMotion[axis] < 8; ++i) {
                    if (isChessboardControl(piece.position.posX + xAxisMotion[axis], piece.position.posY + yAxisMotion[axis], chessboard, piece)) {
                        threatenedPieces[{piece.position.posX + xAxisMotion[axis], piece.position.posY + yAxisMotion[axis]}] = true;
                        break;
                    }
                    if (piece.color == chessboard[piece.position.posX + xAxisMotion[axis]][piece.position.posY + yAxisMotion[axis]].color)
                        break;
                }
            }
        }
            break;
        
        default:
            break;
        }
    }
    
    /// <summary>
    /// T�m tehdit edilen ta�lar�n bulunmas�n� sa�lar.
    /// </summary>
    /// <param name="chessboard">Santran� Tahtas�</param>
    void findThreatenedCell(std::vector<std::vector<Piece>>& chessboard) {

        for (const auto& xAxis : chessboard) {
            for (const auto& piece : xAxis) {
                if (piece.pieceType != PieceType::IDLE || piece.color != Color::IDLE)
                    findThreatenedCellsByPiece(piece, chessboard);
            }
        }
    }

    /// <summary>
    /// Santran� ta��n�n hesaplamaya al�nacak katsay� de�erinin belirlenmesi, 
    /// tehdit durumunda ise 2'ye b�l�necek, de�ilse default hesaplama katsay�s� dikkate al�nacak
    /// </summary>
    /// <param name="piece">Santran� Ta��</param>
    /// <param name="isThreatened">Tehdit durumunu tutan de�i�ken</param>
    /// <returns></returns>
    double calculatePieceScore(Piece& piece, bool isThreatened) override
    {
        if (isThreatened) {
            return pieceScores[piece.pieceType] / 2.0;
        }
        return pieceScores[piece.pieceType];
    }

};
