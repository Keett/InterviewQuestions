#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "Piece.h"
#include "Chessboard.h"

__interface ICalculateScore
{
public:
	virtual bool isChessboardControl(int newPosX, int newPosY, std::vector<std::vector<Piece>>& chessboard, const Piece& piece) = 0;
	virtual void findThreatenedCellsByPiece(const Piece& piece, std::vector<std::vector<Piece>>& chessboard) = 0;
	virtual double calculatePieceScore(Piece& piece, bool is_threatened) = 0;
	virtual std::map<std::string, double> calculateScore(std::vector<std::vector<Piece>>& chessboard) = 0;
};


