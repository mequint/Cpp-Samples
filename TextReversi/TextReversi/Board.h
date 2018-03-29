#pragma once

#include <vector>

#include "Move.h"
#include "Piece.h"

// The 2D directions for the board operations
const int UP = -1;
const int DOWN = 1;
const int LEFT = -1;
const int RIGHT = 1;

class Board
{
	public:
		Board();

		void Reset();

		bool IsMoveValid(const int cellRow, const int cellCol, Piece currentPiece);
		void MakeMove(const int cellRow, const int cellCol, Piece currentPiece);
		
		Piece GetCell(const int row, const int col) const;
		void SetCell(const int row, const int col, Piece piece);

		bool AreMovesAvailable(Piece currentPiece);

	private:
		std::vector<std::vector<Piece>> board;

		void FlipPieces(const int cellRow, const int cellCol, Piece currentPiece);
};