#include "Input.h"

#include <iostream>

char AskYesOrNoQuestion(std::string question)
{
	char response;

	do
	{
		std::cout << question << " (y/n): ";
		std::cin >> response;

		response = tolower(response);
	} while (response != 'y' && response != 'n');

	return response;
}

Move RequestMove()
{
	char letter;
	int columnValue;
	Move move;

	do
	{
		std::cout << "Please enter a letter (a-h), then a number(1-8): ";
		std::cin >> letter >> columnValue;

		letter = tolower(letter);

		if (letter >= 'a' && letter <= 'h')
		{
			// Convert the letter into a cell value
			move.Row = (int)(letter - 'a');
		}
		else
		{
			std::cout << "Invalid letter." << std::endl;
		}
	} while (letter < 'a' && letter > 'h' && columnValue < 1 && columnValue > 8);

	// Take the column value and subtract by 1 to obtain a zero indexed value
	move.Col = columnValue - 1;

	return move;
}

Piece GetPlayerPiece()
{
	char goFirst = AskYesOrNoQuestion("Player 1, would you like to go first?");

	if (tolower(goFirst) == 'y')
	{
		std::cout << "\nPlayer 1 is 'X' and Player 2 is 'O'\n";
		return Piece::X;
	}

	std::cout << "\nPlayer 1 is 'O' and Player 2 is 'X'\n";
	return Piece::O;
}

Move GetPlayerMove(Board& board, Piece currentPlayer)
{
	Move move = RequestMove();

	while (!board.IsMoveValid(move.Row, move.Col, currentPlayer))
	{
		std::cout << std::endl << "Invalid move." << std::endl;
		move = RequestMove();
	}

	return move;
}