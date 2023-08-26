#pragma once
#include <map>

enum class Color {
    IDLE,
    SIYAH,
    BEYAZ
};

enum class PieceType {
    IDLE,
    SAH,
    VEZIR,
    KALE,
    FIL,
    AT,
    P�YON
};
struct Position {
    int posX;
    int posY;
};

class Piece
{
public:
   /* Piece();
    ~Piece();*/

    Color color;
    PieceType pieceType;
    Position position;

private:

};
