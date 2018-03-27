#pragma once

#include <vector>

#include "Piece.h"

// Total number of squares on the board
const int NUM_SQUARES = 64;

// The 2D directions for the board operations
const int UP = -1;
const int DOWN = 1;
const int LEFT = -1;
const int RIGHT = 1;

struct Move
{
	int Row;
	int Col;
};

class Board
{
	public:
		Board();

		void Reset();

		bool IsMoveValid(const int cellRow, const int cellCol, Piece currentPiece);
		void MakeMove(const int cellRow, const int cellCol, Piece currentPiece);

		Piece GetCell(const int row, const int col) const;

	private:
		std::vector<std::vector<Piece>> board;

		void FlipPieces(int cellIndex, Piece currentPiece);
		void FlipPieces(const int cellRow, const int cellCol, Piece currentPiece);
};