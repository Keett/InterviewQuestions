#include "ParseChessboard.h"

class ParseChessboard : public IParseChessboard
{
public:
    const int CHESSBOARD_SIZE = 8;
    // Inherited via IParseChessboard
    virtual std::vector<std::vector<Piece>> parse() override
    {
        std::ifstream dosya("board.txt");
        if (!dosya.is_open()) {
            std::cerr << "Dosya açýlamadý." << std::endl;
        }

        std::vector<std::vector<Piece>> chessboard(CHESSBOARD_SIZE, std::vector<Piece>(CHESSBOARD_SIZE));

        std::string satir;
        for (int i = 0; i < CHESSBOARD_SIZE; ++i) {
            if (std::getline(dosya, satir)) {
                std::istringstream iss(satir);
                for (int j = 0; j < CHESSBOARD_SIZE; ++j) {
                    std::string pieceStr;
                    if (iss >> pieceStr) {
                        if (pieceStr != "--") {
                            Piece piece;
                            piece.color = (pieceStr[1] == 's' ? Color::SIYAH : Color::BEYAZ);
                            piece.pieceType = parsePieceType(pieceStr[0]);
                            piece.position.posX = i;
                            piece.position.posY = j;
                            chessboard[i][j] = piece;
                        }
                        else if (pieceStr == "--")
                        {
                            Piece piece;
                            piece.color = Color::IDLE;
                            piece.pieceType = PieceType::IDLE;
                            piece.position.posX = i;
                            piece.position.posY = j;
                            chessboard[i][j] = piece;
                        }
                    }
                }
            }
        }

        dosya.close();

        printChessboard(chessboard);
        return chessboard;
        //return std::vector<std::vector<Piece>>();    chessboard dolmadýðýnda file açýlmadýðýnda TODO
    }

private:

    // Inherited via IParseChessboard
    virtual void printChessboard(const std::vector<std::vector<Piece>>& chessboard) override
    {
        for (int i = 0; i < CHESSBOARD_SIZE; ++i) {
            for (int j = 0; j < CHESSBOARD_SIZE; ++j) {
                if (chessboard[i][j].pieceType == PieceType::PÝYON) {
                    std::cout << (chessboard[i][j].color == Color::SIYAH ? "ps" : "pb");
                }
                else if (chessboard[i][j].pieceType == PieceType::KALE) {
                    std::cout << (chessboard[i][j].color == Color::SIYAH ? "ks" : "kb");
                }
                else if (chessboard[i][j].pieceType == PieceType::FIL) {
                    std::cout << (chessboard[i][j].color == Color::SIYAH ? "fs" : "fb");
                }
                else if (chessboard[i][j].pieceType == PieceType::AT) {
                    std::cout << (chessboard[i][j].color == Color::SIYAH ? "as" : "ab");
                }
                else if (chessboard[i][j].pieceType == PieceType::VEZIR) {
                    std::cout << (chessboard[i][j].color == Color::SIYAH ? "vs" : "vb");
                }
                else if (chessboard[i][j].pieceType == PieceType::SAH) {
                    std::cout << (chessboard[i][j].color == Color::SIYAH ? "ss" : "sb");
                }
                else {
                    std::cout << "--";
                }

                std::cout << " ";
            }
            std::cout << "\n";
        }
    }
    virtual PieceType parsePieceType(char typeChar) override
    {
        switch (typeChar) {
        case 's': return PieceType::SAH;
        case 'v': return PieceType::VEZIR;
        case 'k': return PieceType::KALE;
        case 'f': return PieceType::FIL;
        case 'a': return PieceType::AT;
        case 'p': return PieceType::PÝYON;
        case '--': return PieceType::IDLE;
        }
    }  
    
};