#include "Display.h"

#include "Input.h"

#include <iostream>
#include <string>

void DisplayBoard(const Board& board)
{
	std::cout << "\n  1   2   3   4   5   6   7   8 ";
	for (int row = 0; row < 8; ++row)
	{
		bool first = true;
		std::cout << "\n" << (char)(row + 'a');
		for (int col = 0; col < 8; ++col)
		{
			std::cout << " " << PieceToChar(board.GetCell(row, col)) << " ";

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