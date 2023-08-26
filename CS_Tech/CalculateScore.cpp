#include "CalculateScore.h"

class CalculateScore : public ICalculateScore
{
public:
    virtual void calculateScore(std::vector<std::vector<Piece>>& chessboard) {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                Piece piece = chessboard[row][col];
                if (piece.pieceType != PieceType::IDLE || piece.color != Color::IDLE) {
                    findThreatenedCells(piece, chessboard);
                }
            }
        }

        // Taþlarýn puanlarýný hesapla
        double total_white_score = 0;
        double total_black_score = 0;

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                Piece piece = chessboard[row][col];
                bool is_threatened = threatened_pieces[{row, col}];

                if (piece.pieceType != PieceType::IDLE || piece.color != Color::IDLE) {
                    if (piece.color == Color::SIYAH) {
                        total_black_score += calculatePieceScore(piece, is_threatened);
                    }
                    else {
                        total_white_score += calculatePieceScore(piece, is_threatened);
                    }
                }
            }
        }

        /*scoreMap["WhiteScore"] = total_white_score;
        scoreMap["BlackScore"] = total_black_score;*/

        std::cout << "White Score: " << total_white_score << std::endl;
        std::cout << "Black Score: " << total_black_score << std::endl;
    }

private:
    std::map<std::pair<int, int>, bool> threatened_pieces;
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
    virtual bool isChessboardControl(int newPosX, int newPosY, std::vector<std::vector<Piece>>& chessboard, const Piece& piece) override
    {
        if (newPosX >= 0 && newPosX < 8 &&
            newPosY >= 0 && newPosY < 8 &&
            chessboard[newPosX][newPosY].pieceType != PieceType::IDLE &&
            piece.color != chessboard[newPosX][newPosY].color) {
            return true;
        }
        return false;
    }

    virtual void findThreatenedCells(const Piece& piece, std::vector<std::vector<Piece>>& chessboard) override
    {
        switch (piece.pieceType) {
        case PieceType::PÝYON:
            // Piyonun hareket kurallarýna göre tehdit ettiði hücreleri ekleyebilirsiniz.
            // Örneðin, taþýn rengine göre ileri sol ve sað hücreleri tehdit edebilir.
            // Piyon tehditleri

        {
            int dy[] = { -1, 1 };
            int newRow = -1;
            int newCol = -1;

            for (int i = 0; i < 2; ++i) {
                newRow = (piece.color == Color::BEYAZ) ? (piece.position.posX - 1) : (piece.position.posX + 1);
                newCol = (piece.position.posY) + dy[i];

                if (isChessboardControl(newRow, newCol, chessboard, piece)) {
                    threatened_pieces[{newRow, newCol}] = true;
                }
            }
        }
        break;

        case PieceType::AT:
            // Atýn hareket kurallarýna göre tehdit ettiði hücreleri ekleyebilirsiniz.
            // Örneðin, L þeklinde hareket ederek diðer hücreleri tehdit eder.
            // (2 yukarý-1 sola, 2 yukarý-1 saða, 2 sola-1 yukarý, 2 saða-1 yukarý, vb.)
        {
            int dx[] = { 2, 2, 1, 1, -1, -1, -2, -2 };
            int dy[] = { 1, -1, 2, -2, 2, -2, 1, -1 };
            for (int i = 0; i < 8; ++i) {
                int newRow = piece.position.posX + dx[i];
                int newCol = piece.position.posY + dy[i];

                if (isChessboardControl(newRow, newCol, chessboard, piece)) {
                    threatened_pieces[{newRow, newCol}] = true;
                }
            }
        }
        break;

        case PieceType::VEZIR:
            //Vezir tehditleri
            for (int i = 1; piece.position.posX + i < 8; ++i) {
                if (isChessboardControl(piece.position.posX + i, piece.position.posY, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX + i, piece.position.posY}] = true;  // Aþaðý
                    break;
                }
                if (piece.color == chessboard[piece.position.posX + i][piece.position.posY].color) {
                    break;
                }
            }
            for (int i = 1; piece.position.posX - i >= 0; ++i) {
                if (isChessboardControl(piece.position.posX - i, piece.position.posY, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX - i, piece.position.posY}] = true;  // Yukarý
                    break;
                }
                if (piece.color == chessboard[piece.position.posX - i][piece.position.posY].color)
                    break;
            }
            for (int i = 1; piece.position.posY + i < 8; ++i) {
                if (isChessboardControl(piece.position.posX, piece.position.posY + i, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX, piece.position.posY + i}] = true;  // Sað
                    break;
                }
                if (piece.color == chessboard[piece.position.posX][piece.position.posY + i].color)
                    break;
            }
            for (int i = 1; piece.position.posY - i >= 0; ++i) {
                if (isChessboardControl(piece.position.posX, piece.position.posY - i, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX, piece.position.posY - i}] = true;  // Sol
                    break;
                }
                if (piece.color == chessboard[piece.position.posX][piece.position.posY - i].color)
                    break;
            }
            for (int i = 1; piece.position.posX + i < 8 && piece.position.posY + i < 8; ++i) {
                if (isChessboardControl(piece.position.posX + i, piece.position.posY + i, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX + i, piece.position.posY + i}] = true;  // Sað üst
                    break;
                }
                if (piece.color == chessboard[piece.position.posX + i][piece.position.posY + i].color)
                    break;
            }
            for (int i = 1; piece.position.posX + i < 8 && piece.position.posY - i >= 0; ++i) {
                if (isChessboardControl(piece.position.posX + i, piece.position.posY - i, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX + i, piece.position.posY - i}] = true;  // Sol üst
                    break;
                }
                if (piece.color == chessboard[piece.position.posX + i][piece.position.posY - i].color)
                    break;
            }
            for (int i = 1; piece.position.posX - i >= 0 && piece.position.posY + i < 8; ++i) {
                if (isChessboardControl(piece.position.posX - i, piece.position.posY + i, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX - i, piece.position.posY + i}] = true;  // Sað alt
                    break;
                }
                if (piece.color == chessboard[piece.position.posX - i][piece.position.posY + i].color)
                    break;
            }
            for (int i = 1; piece.position.posX - i >= 0 && piece.position.posY - i >= 0; ++i) {
                if (isChessboardControl(piece.position.posX - i, piece.position.posY - i, chessboard, piece)) {
                    threatened_pieces[{piece.position.posX - i, piece.position.posY - i}] = true;  // Sol alt
                    break;
                }
                if (piece.color == chessboard[piece.position.posX - i][piece.position.posY - i].color)
                    break;
            }
            break;

        default:
            break;
        }
    }

    virtual double calculatePieceScore(Piece& piece, bool is_threatened) override
    {
        if (is_threatened) {
            return pieceScores[piece.pieceType] / 2.0;
        }
        return pieceScores[piece.pieceType];
    }

};
