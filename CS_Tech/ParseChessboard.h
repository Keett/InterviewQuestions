#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Piece.h"
#include "Chessboard.h"

__interface IParseChessboard {
public:
	virtual std::vector<std::vector<Piece>> parse() = 0;
	virtual void printChessboard(const std::vector<std::vector<Piece>>& chessboard) = 0;
	virtual PieceType parsePieceType(char typeChar) = 0;
};
