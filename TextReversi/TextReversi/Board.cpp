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
	for (auto& row : board)
	{
		for (auto& cell : row)
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
	flipPieces(cellRow, cellCol, currentPiece);
}

void Board::SetCell(const int row, const int col, Piece piece)
{
	board[row][col] = piece;
}

Piece Board::GetCell(const int row, const int col) const
{
	return board[row][col];
}

bool Board::AreMovesAvailable(Piece currentPiece)
{
	for (int row = 0; row < (int)board.size(); ++row)
	{
		for (int col = 0; col < (int)board[row].size(); ++col)
		{
			if (GetCell(row, col) == Piece::EMPTY && IsMoveValid(row, col, currentPiece))
			{
				return true;
			}
		}
	}

	return false;
}

std::vector<Cell> Board::GetAvailableMoves(Piece currentPiece)
{
	std::vector<Cell> cells;
	for (int row = 0; row < (int)board.size(); ++row)
	{
		for (int col = 0; col < (int)board[row].size(); ++col)
		{
			if (GetCell(row, col) == Piece::EMPTY && IsMoveValid(row, col, currentPiece))
			{
				cells.emplace_back(row, col);
			}
		}
	}

	return cells;
}

// Helper methods
void Board::flipPieces(const int cellRow, const int cellCol, Piece currentPiece)
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

			std::stack<Cell> cellIndices;
			while (!isOutOfBounds && board[nextRow][nextCol] == opponentPiece)
			{
				Cell cell = { nextRow, nextCol };
				cellIndices.push(cell);

				nextRow += row;
				nextCol += col;

				isOutOfBounds = (nextRow < 0 || nextRow >(int)(board.size() - 1)) ||
					(nextCol < 0 || nextCol >(int)(board[nextRow].size() - 1));

				if (!isOutOfBounds && board[nextRow][nextCol] == currentPiece)
				{
					while (!cellIndices.empty())
					{
						Cell topCell = cellIndices.top();
						cellIndices.pop();

						board[topCell.Row][topCell.Col] = currentPiece;
					}
				}
			}
		}
	}
}