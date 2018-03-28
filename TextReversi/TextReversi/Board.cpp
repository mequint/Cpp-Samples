#include "Board.h"

#include <stack>

Board::Board() :
	board(8, std::vector<Piece>(8, Piece::EMPTY))
{
	board[3][3] = Piece::X;
	board[3][4] = Piece::O;
	board[4][3] = Piece::O;
	board[4][4] = Piece::X;
}

void Board::Reset()
{
	for (auto row : board)
	{
		for (auto cell : row)
		{
			cell = Piece::EMPTY;
		}
	}

	board[3][3] = Piece::X;
	board[3][4] = Piece::O;
	board[4][3] = Piece::O;
	board[4][4] = Piece::X;
}

bool Board::IsMoveValid(const int cellRow, const int cellCol, Piece currentPiece)
{
	if (board[cellRow][cellCol] != Piece::EMPTY) return false;

	for (int row = UP; row <= DOWN; ++row)
	{
		for (int col = LEFT; col <= RIGHT; ++col)
		{
			// This is where the current players piece could be placed
			if (row == 0 && col == 0) continue;

			Piece opponentPiece = OppositePiece(currentPiece);
			
			int nextRow = cellRow + row;
			int nextCol = cellCol + col;

			bool isOutOfBounds = (nextRow < 0 || nextRow > (int)(board.size() - 1)) ||
				(nextCol < 0 || nextCol > (int)(board[nextRow].size() - 1));

			while (!isOutOfBounds && board[nextRow][nextCol] == opponentPiece)
			{
				nextRow += row;
				nextCol += col;

				isOutOfBounds = (nextRow < 0 || nextRow > (int)(board.size() - 1)) ||
					(nextCol < 0 || nextCol > (int)(board[nextRow].size() - 1));

				if (!isOutOfBounds && board[nextRow][nextCol] == currentPiece)
					return true;
			}
		}
	}

	return false;
}

void Board::MakeMove(const int cellRow, const int cellCol, Piece currentPiece)
{
	board[cellRow][cellCol] = currentPiece;
	FlipPieces(cellRow, cellCol, currentPiece);
}

Piece Board::GetCell(const int row, const int col) const
{
	return board[row][col];
}


bool Board::AreMovesAvailable(Piece currentPiece)
{
	for (int row = 0; row < board.size(); ++row)
	{
		for (int col = 0; col < board[row].size(); ++col)
		{
			if (GetCell(row, col) == Piece::EMPTY && IsMoveValid(row, col, currentPiece))
			{
				return true;
			}
		}
	}

	return false;
}

// Helper methods
void Board::FlipPieces(const int cellRow, const int cellCol, Piece currentPiece)
{
	for (int row = UP; row <= DOWN; ++row)
	{
		for (int col = LEFT; col <= RIGHT; ++col)
		{
			// This is where the current players piece was placed
			if (row == 0 && col == 0) continue;

			Piece opponentPiece = OppositePiece(currentPiece);

			int nextRow = cellRow + row;
			int nextCol = cellCol + col;

			bool isOutOfBounds = (nextRow < 0 || nextRow >(int)(board.size() - 1)) ||
				(nextCol < 0 || nextCol >(int)(board[nextRow].size() - 1));

			std::stack<Move> cellIndices;
			while (!isOutOfBounds && board[nextRow][nextCol] == opponentPiece)
			{
				Move cellIndex = { nextRow, nextCol };
				cellIndices.push(cellIndex);

				nextRow += row;
				nextCol += col;

				isOutOfBounds = (nextRow < 0 || nextRow >(int)(board.size() - 1)) ||
					(nextCol < 0 || nextCol >(int)(board[nextRow].size() - 1));

				if (!isOutOfBounds && board[nextRow][nextCol] == currentPiece)
				{
					while (!cellIndices.empty())
					{
						Move cellIndex = cellIndices.top();
						cellIndices.pop();

						board[cellIndex.Row][cellIndex.Col] = currentPiece;
					}
				}
			}
		}
	}
}