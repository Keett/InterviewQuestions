#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Piece.h"

__interface IParseChessboard {
public:

	virtual void printChessboard(const std::vector<std::vector<Piece>>& chessboard) = 0;
	virtual PieceType parsePieceType(char typeChar) = 0;
	virtual std::vector<std::vector<Piece>> parse() = 0;

};
