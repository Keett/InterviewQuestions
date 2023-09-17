#include "CalculateScore.h"

class CalculateScore : public ICalculateScore
{
public:

    /// <summary>
    /// Tüm taþlarýn katsayýsýna göre puanlamalarýnýn hesaplanmasýný saðlar.
    /// </summary>
    /// <param name="chessboard">Santranç Tahtasý</param>
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
        {PieceType::PÝYON, 1},
        {PieceType::AT, 3},
        {PieceType::FIL, 3},
        {PieceType::KALE, 5},
        {PieceType::VEZIR, 9},
        {PieceType::SAH, 100}
    };

    // Inherited via ICalculateScore

    /// <summary>
    /// Santraç taþýnýn tehdit durumlarýnýn kontrolü için oluþturulmuþ ortak logic yapýsý
    /// (Bulunan tehdit alaný santranç taþýnýn alanýnýn içinde mi?,
    /// Santranç tahtasýnda bulunan pozisyon deðerlerinde taþ var mý?,
    /// bulunan taþ tehdit mi?)
    /// </summary>
    /// <param name="newPosX">Bulunan yeni posX deðeri</param>
    /// <param name="newPosY">Bulunan yeni posY deðeri</param>
    /// <param name="chessboard">Santranç Tahtasý</param>
    /// <param name="piece">Santranç Taþý</param>
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
    /// Taþa göre tehdit edilen santranç taþlarýnýn konumlarýnýn bulunmasýný saðlar.
    /// </summary>
    /// <param name="piece">Santranç Taþý</param>
    /// <param name="chessboard">Santranç Tahtasý</param>
    void findThreatenedCellsByPiece(const Piece& piece, std::vector<std::vector<Piece>>& chessboard) override
    {
        switch (piece.pieceType) {
        /// <summary>
        /// Piyon tehditleri
        /// Beyaz piyonlarýn yukarý yönlü ve siyah piyonlarýn aþaðý yönlü hareketi mevcuttur.
        /// Bu sebeple newPosX deðerleri renge göre kontrol edilmektedir.
        /// </summary>
        /// <param name="piece">Santranç Taþý</param>
        /// <param name="chessboard">Santraç Tahtasý</param>
        case PieceType::PÝYON:
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
        /// L þeklinde tehdit hareketleri mevcut (2 yukarý - 1 sola, 2 yukarý - 1 saða, 2 sola - 1 yukarý, 2 saða - 1 yukarý gibi.)
        /// </summary>
        /// <param name="piece">Santranç Taþý</param>
        /// <param name="chessboard">Santraç Tahtasý</param>
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
        /// Vezirin çapraz ve düz eksenli hareketi mevcuttur.
        /// Vezirin hareketi kendi grubundan taþa kadar devam eder, kendi grubundan deðilse tehdittir.  
        /// </summary>
        /// <param name="piece">Santranç Taþý</param>
        /// <param name="chessboard">Santranç Tahtasý</param>
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
    /// Tüm tehdit edilen taþlarýn bulunmasýný saðlar.
    /// </summary>
    /// <param name="chessboard">Santranç Tahtasý</param>
    void findThreatenedCell(std::vector<std::vector<Piece>>& chessboard) {

        for (const auto& xAxis : chessboard) {
            for (const auto& piece : xAxis) {
                if (piece.pieceType != PieceType::IDLE || piece.color != Color::IDLE)
                    findThreatenedCellsByPiece(piece, chessboard);
            }
        }
    }

    /// <summary>
    /// Santranç taþýnýn hesaplamaya alýnacak katsayý deðerinin belirlenmesi, 
    /// tehdit durumunda ise 2'ye bölünecek, deðilse default hesaplama katsayýsý dikkate alýnacak
    /// </summary>
    /// <param name="piece">Santranç Taþý</param>
    /// <param name="isThreatened">Tehdit durumunu tutan deðiþken</param>
    /// <returns></returns>
    double calculatePieceScore(Piece& piece, bool isThreatened) override
    {
        if (isThreatened) {
            return pieceScores[piece.pieceType] / 2.0;
        }
        return pieceScores[piece.pieceType];
    }

};
