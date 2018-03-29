#include "Display.h"

#include "Input.h"

#include <iostream>
#include <string>

void DisplayInstructions()
{
	char response;

	std::cout << "Welcome to TextReversi\n";

	response = AskYesOrNoQuestion("Would you like to read the instructions?");
	if (response == 'y')
	{
		std::cout << "Try to get more pieces than your opponent by selecting a spot\n";
		std::cout << "on the board that has my pieces between one or more\n";
		std::cout << "of your other pieces by selecting a letter(a-h)\n";
		std::cout << "followed by a number (1-8) that corresponds to the\n";
		std::cout << "following grid.\n\n";

		std::cout << " a1 | a2 | a3 | a4 | a5 | a6 | a7 | a8 \n";
		std::cout << "---------------------------------------\n";
		std::cout << " b1 | b2 | b3 | b4 | b5 | b6 | b7 | b8 \n";
		std::cout << "---------------------------------------\n";
		std::cout << " c1 | c2 | c3 | c4 | c5 | c6 | c7 | c8 \n";
		std::cout << "---------------------------------------\n";
		std::cout << " d1 | d2 | d3 | d4 | d5 | d6 | d7 | d8 \n";
		std::cout << "---------------------------------------\n";
		std::cout << " e1 | e2 | e3 | e4 | e5 | e6 | e7 | e8 \n";
		std::cout << "---------------------------------------\n";
		std::cout << " f1 | f2 | f3 | f4 | f5 | f6 | f7 | f8 \n";
		std::cout << "---------------------------------------\n";
		std::cout << " g1 | g2 | g3 | g4 | g5 | g6 | g7 | g8 \n";
		std::cout << "---------------------------------------\n";
		std::cout << " h1 | h2 | h3 | h4 | h5 | h6 | h7 | h8 \n\n";
	}

	std::cout << "Let the game begin!\n\n";
}

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

void DisplayWinner(Piece player1, Piece player2, int finalX, int finalO)
{
	std::cout << std::endl;
	if (finalX > finalO)
	{
		std::string winner = (player1 == Piece::X) ? "Player 1" : "Player 2";
		std::cout << winner << " wins!" << std::endl;
	}
	else if (finalX < finalO)
	{
		std::string winner = (player1 == Piece::O) ? "Player 1" : "Player 2";
		std::cout << winner << " wins!" << std::endl;
	}
	else
	{
		std::cout << "The game was a draw..." << std::endl;
	}
}