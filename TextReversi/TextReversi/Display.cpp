#include "Display.h"

#include "Input.h"

#include <iostream>
#include <string>

char PieceOrAvailableMoveToChar(const Board& board, int row, int col, const std::vector<Cell>& availableMoves)
{
	Piece piece = board.GetCell(row, col);

	// Check to see if we have an available move
	if (piece == Piece::EMPTY)
	{
		for (auto cell : availableMoves)
		{
			if (cell.Row == row && cell.Col == col)
			{
				// Add an asterisk to mark an available move
				return '*';
			}
		}
	}

	return PieceToChar(piece);
}

void DisplayBoard(const Board& board, const std::vector<Cell>& availableMoves)
{
	std::cout << "\n  1   2   3   4   5   6   7   8 ";
	for (int row = 0; row < 8; ++row)
	{
		bool first = true;
		std::cout << "\n" << (char)(row + 'a');
		for (int col = 0; col < 8; ++col)
		{
			std::cout << " " << PieceOrAvailableMoveToChar(board, row, col, availableMoves) << " ";

			if (col != 7)
			{
				std::cout << "|";
			}
		}

		if (row != 7)
		{
			std::cout << "\n--------------------------------";
		}
	}
	std::cout << std::endl;
}

void DisplayCurrentScore(int xScore, int oScore)
{
	std::cout << std::endl << "X = " << xScore << "\tO = " << oScore;
}

void DisplayWhoseTurn(Piece currentPlayer)
{
	char player = PieceToChar(currentPlayer);
	std::cout << "\t" << "It is " << player << "s turn" << std::endl;
}