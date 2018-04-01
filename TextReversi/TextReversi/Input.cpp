#include "Input.h"

#include <algorithm>
#include <iostream>
#include <string>

char AskYesOrNoQuestion(std::string question)
{
	char response;

	do
	{
		std::cout << question << " (y/n): ";
		std::cin >> response; std::cin.ignore();

		response = tolower(response);
	} while (response != 'y' && response != 'n');

	return response;
}

Move RequestMove()
{
	Move move;

	bool invalid = true;
	do
	{
		std::cout << "Please enter a letter (a-h), then a number(1-8): ";

		std::string line;
		getline(std::cin, line);

		// Change the line to lowercase
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);

		if (line.length() == 2)
		{
			// Convert the letter into a cell value
			if (line[0] >= 'a' && line[0] <= 'h' && line[1] >= '1' && line[1] <= '8')
			{
				move.Row = (int)(line[0] - 'a');
				move.Col = (int)(line[1] - '1');
				move.Command = Command::Move;
				invalid = false;
			}
		}
		else if (line == "save")
		{
			move.Command = Command::Save;
			invalid = false;
		}
		else if (line == "load")
		{
			move.Command = Command::Load;
			invalid = false;
		}
		else if (line == "quit" || line == "exit")
		{
			move.Command = Command::Quit;
			invalid = false;
		}
		else if (line == "board")
		{
			move.Command = Command::PrintBoard;
			invalid = false;
		}
		else if (line == "options")
		{
			move.Command = Command::Options;
			invalid = false;
		}
		else
		{
			std::cout << "Invalid input." << std::endl;
		}
	} while (invalid);

	return move;
}

Move GetPlayerMove(Board& board, Piece currentPlayer)
{
	Move move = RequestMove();

	while (move.Command == Command::Move && !board.IsMoveValid(move.Row, move.Col, currentPlayer))
	{
		std::cout << std::endl << "Invalid move." << std::endl;
		move = RequestMove();
	}

	return move;
}