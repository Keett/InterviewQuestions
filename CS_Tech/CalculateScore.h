#pragma once

#include <iostream>
#include "Piece.h"
#include <vector>

__interface ICalculateScore
{
public:
	virtual bool isChessboardControl(int newPosX, int newPosY, std::vector<std::vector<Piece>>& chessboard, const Piece& piece) = 0;
	virtual void findThreatenedCells(const Piece& piece, std::vector<std::vector<Piece>>& chessboard) = 0;
	virtual double calculatePieceScore(Piece& piece, bool is_threatened) = 0;
	virtual void calculateScore(std::vector<std::vector<Piece>>& chessboard) = 0;
};


