#include "Board.h"

#include <stack>

Board::Board() :
	board(NUM_SQUARES, Piece::EMPTY)
{
	board[27] = Piece::X;
	board[28] = Piece::O;
	board[35] = Piece::O;
	board[36] = Piece::X;
}

void Board::Reset()
{
	for (auto cell : board)
	{
		cell = Piece::EMPTY;
	}

	board[27] = Piece::X;
	board[28] = Piece::O;
	board[35] = Piece::O;
	board[36] = Piece::X;
}

bool Board::IsMoveValid(const int index, Piece currentPiece)
{
	if (board[index] != Piece::EMPTY) return false;
	
	for (int row = UP; row <= DOWN; ++row)
	{
		for (int col = LEFT; col <= RIGHT; ++col)
		{
			if (row == 0 && col == 0) continue;

			Piece opponentPiece = OppositePiece(currentPiece);
			int cellMove = row * 8 + col;
			int nextIndex = index + cellMove;

			bool isOutOfBounds = (nextIndex < 0 || nextIndex  >(int)board.size() - 1);

			while (!isOutOfBounds && board[nextIndex] == opponentPiece)
			{
				nextIndex += cellMove;

				// Check for out of bounds
				isOutOfBounds = (nextIndex < 0 || nextIndex  >(int)board.size() - 1);

				// Return true if the move is valid
				if (!isOutOfBounds && board[nextIndex] == currentPiece)
					return true;
			}
		}
	}

	// The move is invalid
	return false;
}

void Board::MakeMove(const int index, Piece currentPiece)
{
	board[index] = currentPiece;
	FlipPieces(index, currentPiece);
}		

Piece Board::GetCell(const int row, const int col) const
{
	return board[row * 8 + col];
}


// Helper methods
void Board::FlipPieces(const int cellIndex, Piece currentPiece)
{
	for (int row = UP; row <= DOWN; ++row)
	{
		for (int col = LEFT; col <= RIGHT; ++col)
		{
			if (row == 0 && col == 0) continue;
			
			Piece opponentPiece = OppositePiece(currentPiece);

			int cellMove = row * 8 + col;
			int nextIndex = cellIndex + cellMove;

			bool isOutOfBounds = (nextIndex < 0 || nextIndex > (int)board.size() - 1);

			std::stack<int> cellIndices;
			while (!isOutOfBounds && board[nextIndex] == opponentPiece)
			{
				cellIndices.push(nextIndex);

				nextIndex += cellMove;
				isOutOfBounds = (nextIndex < 0 || nextIndex >(int)board.size() - 1);

				if (!isOutOfBounds && board[nextIndex] == currentPiece)
				{
					while (!cellIndices.empty())
					{
						int index = cellIndices.top();
						cellIndices.pop();

						board[index] = currentPiece;
					}
				}
			}
		}
	}
}