#include "ParseChessboard.h"

class ParseChessboard : public IParseChessboard
{
public:
    // Inherited via IParseChessboard
    /// <summary>
    /// txt dosyasýný parse eder ve chessboard'u geri döndürür
    /// </summary>
    /// <returns>chessboard map</returns>
    std::vector<std::vector<Piece>> parse() override
    {
        std::ifstream boardFile("board.txt");
        if (!boardFile.is_open()) {
            std::cerr << "Board file is not open." << std::endl;
            return std::vector<std::vector<Piece>>();
        }
        std::vector<std::vector<Piece>> chessboard(Chessboard::CHESSBOARD_SIZE, std::vector<Piece>(Chessboard::CHESSBOARD_SIZE));

        std::string line;
        for (int i = 0; i < Chessboard::CHESSBOARD_SIZE; ++i) {
            if (std::getline(boardFile, line)) {
                std::istringstream iss(line);
                for (int j = 0; j < Chessboard::CHESSBOARD_SIZE; ++j) {
                    std::string pieceStr;
                    if (iss >> pieceStr) {
                        chessboard[i][j] = (pieceStr != "--") ? 
                            Piece((pieceStr[1] == 's' ? Color::SIYAH : Color::BEYAZ), parsePieceType(pieceStr[0]), i, j) : 
                            Piece(Color::IDLE, PieceType::IDLE, i, j);
                    }
                }
            }
        }
        printChessboard(chessboard);
        return chessboard;
    }

private:

    // Inherited via IParseChessboard
    /// <summary>
    /// Txt dosyasýndan okunan datalarýn görselleþtirilmesi saðlandý.
    /// </summary>
    /// <param name="chessboard">Santranç Tahtasý</param>
    void printChessboard(const std::vector<std::vector<Piece>>& chessboard) override
    {
        for (const auto& xAxis : chessboard) {
            for (const auto& piece : xAxis) {
                std::string pieceStr;

                switch (piece.pieceType) {
                case PieceType::SAH:   pieceStr = (piece.color == Color::SIYAH) ? "ss" : "sb"; break;
                case PieceType::VEZIR: pieceStr = (piece.color == Color::SIYAH) ? "vs" : "vb"; break;
                case PieceType::KALE:  pieceStr = (piece.color == Color::SIYAH) ? "ks" : "kb"; break;
                case PieceType::FIL:   pieceStr = (piece.color == Color::SIYAH) ? "fs" : "fb"; break;
                case PieceType::AT:    pieceStr = (piece.color == Color::SIYAH) ? "as" : "ab"; break;
                case PieceType::PÝYON: pieceStr = (piece.color == Color::SIYAH) ? "ps" : "pb"; break;
                case PieceType::IDLE:  pieceStr = "--"; break;
                }

                std::cout << pieceStr << " ";
            }
            std::cout << '\n';
        }
    }
    
    /// <summary>
    /// txt dosyasýndan okunan deðerleri PieceType türüne convert eder.
    /// </summary>
    /// <param name="typeChar">Okunan karaktere ait parametre deðiþkeni</param>
    /// <returns>PieceType türünden geri döndürür</returns>
    PieceType parsePieceType(char typeChar) override {
        switch (typeChar) {
        case 's': return PieceType::SAH;
        case 'v': return PieceType::VEZIR;
        case 'k': return PieceType::KALE;
        case 'f': return PieceType::FIL;
        case 'a': return PieceType::AT;
        case 'p': return PieceType::PÝYON;
        default:  return PieceType::IDLE;  // Handle "--" case
        }
    }
    
};