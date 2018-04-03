#include "InGameState.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "Display.h"
#include "StateManager.h"

InGameState::InGameState(StateManager* stateManager) :
	GameState(stateManager),
	m_gameOver(false)
{}

void InGameState::Run()
{
	auto context = m_stateManager->GetContext();

	display(context);

	m_gameOver = false;
	bool movesAvailableLastTurn = true;
	bool exit = false;

	while (!m_gameOver)
	{
		if (context->AreMovesAvailable())
		{
			Move move = getPlayerMove();

			switch (move.Command)
			{
				case InGameCommands::Move:
				{
					context->MakeMove(move.Row, move.Col);
					movesAvailableLastTurn = true;

					if (context->GetTotalMoves() == 64)
					{
						DisplayBoard(context->GetBoard());
						m_gameOver = true;
					}
					else
					{
						context->SetCurrentTurn(OppositePiece(context->GetCurrentTurn()));
						display(context);
					}


					break;
				}

				case InGameCommands::Save:
				{
					std::cout << "Saving game\n";
					std::cout << "Enter a save file name: ";

					std::string filename;
					getline(std::cin, filename);

					context->Save(filename);
					break;
				}

				case InGameCommands::Load:
				{
					std::cout << "\nLoading game\n";

					std::cout << "Enter a game name to load: ";
					std::string filename;
					getline(std::cin, filename);

					if (!context->Load(filename))
					{
						std::cout << "ERROR: Failed to load game /'" << filename << "/'";
					}
					else
					{
						display(context);
					}
					break;
				}
				
				case InGameCommands::Quit:
				{
					std::cout << "\nExiting the game...\n";
					exit = true;
					m_gameOver = true;
					break;
				}

				case InGameCommands::PrintBoard:
				{
					display(context);
					break;
				}

				case InGameCommands::Options:
				{
					std::cout << "[a-h][1-8]:   Make a move\n";
					std::cout << "save [str]:   Save the game\n";
					std::cout << "load [str]:   Load a saved game\n";
					std::cout << "exit/quit:    Exit the game\n";
					std::cout << "board:        Print the board\n";
					std::cout << "options:      Display a list of options\n" << std::endl;
					break;
				}
			}
		} 
		else if (!movesAvailableLastTurn)
		{
			m_gameOver = true;
		}
		else
		{
			movesAvailableLastTurn = false;

			std::cout << "\n" << PieceToChar(context->GetCurrentTurn()) << " was unable to move...\n";

			context->SetCurrentTurn(OppositePiece(context->GetCurrentTurn()));
			display(context);
		}
	}

	// If exiting, we want to go to the main menu
	if (exit)
	{
		m_stateManager->ChangeState(GameStateType::MainMenu);
	}
	// Else, we have a game over condition
	else
	{
		m_stateManager->ChangeState(GameStateType::GameOver);
	}
}

Move InGameState::getPlayerMove()
{	
	auto context = m_stateManager->GetContext();
	Move move = (IsAIPlayersTurn(context, context->GetCurrentTurn())) ? m_reversiAI.RequestMove(context) : requestMove();

	while (move.Command == InGameCommands::Move && !context->GetBoard().IsMoveValid(move.Row, move.Col, context->GetCurrentTurn()))
	{
		std::cout << "\nInvalid move...\n\n";
		move = requestMove();
	}

	return move;
}

void InGameState::display(GameContext* context)
{
	DisplayBoard(context->GetBoard(), context->GetBoard().GetAvailableMoves(context->GetCurrentTurn()));
	DisplayCurrentScore(context->GetXScore(), context->GetOScore());
	DisplayWhoseTurn(context->GetCurrentTurn());
}


bool InGameState::IsAIPlayersTurn(GameContext* context, Piece currentPiece)
{
	Player player1 = context->GetPlayer1();
	Player player2 = context->GetPlayer2();

	if (player1.GetPiece() == currentPiece)
	{
		return !player1.IsHuman();
	}

	return !player2.IsHuman();
}

// Human implementation of the request move
Move InGameState::requestMove()
{
	Move move;

	bool invalid = true;
	do
	{
		std::cout << "\nPlease enter a letter (a-h), then a number(1-8): ";

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
				move.Command = InGameCommands::Move;
				invalid = false;
			}
		}
		else if (line == "save")
		{
			move.Command = InGameCommands::Save;
			invalid = false;
		}
		else if (line == "load")
		{
			move.Command = InGameCommands::Load;
			invalid = false;
		}
		else if (line == "quit" || line == "exit")
		{
			move.Command = InGameCommands::Quit;
			invalid = false;
		}
		else if (line == "board")
		{
			move.Command = InGameCommands::PrintBoard;
			invalid = false;
		}
		else if (line == "options")
		{
			move.Command = InGameCommands::Options;
			invalid = false;
		}
		else
		{
			std::cout << "Invalid input." << std::endl;
		}
	} while (invalid);

	return move;
}