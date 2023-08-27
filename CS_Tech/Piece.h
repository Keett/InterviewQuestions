#pragma once

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
    PÝYON
};
struct Position {
    int posX;
    int posY;
};

class Piece
{
public:

    Piece(Color color, PieceType pieceType, int posX, int posY)
        : color(color), pieceType(pieceType), position({ posX, posY }) {}

    Piece() : color(Color::IDLE), pieceType(PieceType::IDLE), position({ 0, 0 }) {}

    Color color;
    PieceType pieceType;
    Position position;

private:

};