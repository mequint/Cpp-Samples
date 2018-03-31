#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Board.h"
#include "Display.h"
#include "Game.h"
#include "GameStates.h"
#include "Input.h"
#include "Piece.h"
#include "Player.h"
#include "StateManager.h"

// TODO:
//		AI! 
//			*Add a method Board->AvailableMoves as a vector of moves
//			*Have the AI player make a random move based on the moves available
//			*Use backtracking and weighted decision making for the AI to try for the maximum available pieces in a turn
//			*Make the AI smarter by using a heuristic of key placements on the game board
//		Make the TextReversi follow a state based pattern which accesses a "global" game class
//			* New Game state
//			* Load Game state
//			* Game state
//			* GameOver state
//			* Make the state machine and tie it to state classes
//		2.0 - Make the game multiplayer by using Sockets
//		3.0 - 2D or 3D Graphical representation!

int main()
{
	Game textReversi;

	StateManager manager;
	manager.ChangeState(GameStateType::Intro);
	while (manager.IsRunning())
	{
		manager.GetInput();
		manager.Update();
		manager.Display();
	}

	char again = 'y';

	DisplayInstructions();

	while (again == 'y')
	{
		// Move to new game/load game state...
		// determine who gets to play the piece
		Player player1;
		player1.piece = GetPlayerPiece();
		player1.isHuman = true;
		textReversi.SetPlayer1(player1);

		Player player2;
		player2.piece = OppositePiece(player1.piece);
		player2.isHuman = true;
		textReversi.SetPlayer2(player2);

		// Move the display code to InGame and EndGame state
		DisplayBoard(textReversi.GetBoard());
		DisplayCurrentScore(textReversi.GetXScore(), textReversi.GetOScore());
		DisplayWhoseTurn(textReversi.GetCurrentTurn());

		bool gameOver = false;
		while (!gameOver)
		{
			bool movesAvailableLastTurn = true;

			if (textReversi.AreMovesAvailable())
			{
				Board board = textReversi.GetBoard();
				Move move = GetPlayerMove(board, textReversi.GetCurrentTurn());

				std::string filename;

				switch (move.Command)
				{
					case Command::Move:
						textReversi.MakeMove(move.Row, move.Col);

						movesAvailableLastTurn = true;

						if (textReversi.GetTotalMoves() == 64)
							gameOver = true;

						textReversi.SetCurrentTurn(OppositePiece(textReversi.GetCurrentTurn()));

						DisplayBoard(textReversi.GetBoard());
						DisplayCurrentScore(textReversi.GetXScore(), textReversi.GetOScore());
						DisplayWhoseTurn(textReversi.GetCurrentTurn());

						break;

					case Command::Save:
						std::cout << "Saving game" << std::endl;

						std::cout << "Enter a save name: ";
						getline(std::cin, filename);

						textReversi.Save(filename);
						break;

					case Command::Load:
						std::cout << "Loading game" << std::endl;

						std::cout << "Enter a game name to load: ";
						getline(std::cin, filename);

						if (!textReversi.Load(filename))
						{
							std::cout << "ERROR: Failed to load game /'" << filename << "/'";
						}
						
						break;

					case Command::Quit:
						gameOver = true;
						textReversi.Reset();
						break;

					case Command::PrintBoard:
						DisplayBoard(textReversi.GetBoard());
						DisplayCurrentScore(textReversi.GetXScore(), textReversi.GetOScore());
						DisplayWhoseTurn(textReversi.GetCurrentTurn());
						break;

					case Command::Options:
						std::cout << "[a-h][1-8]:   Make a move\n";
						std::cout << "save [str]:   Save the game\n";
						std::cout << "load [str]:   Load a saved game\n";
						std::cout << "quit:         Exit the game\n";
						std::cout << "board:        Print the board\n";
						std::cout << "options:      Display a list of options\n" << std::endl;
						break;
				}
			}
			else if (!movesAvailableLastTurn)
			{
				// No moves are available - end the game
				gameOver = true;
			}
			else
			{
				movesAvailableLastTurn = false;

				textReversi.SetCurrentTurn(OppositePiece(textReversi.GetCurrentTurn()));

				DisplayBoard(textReversi.GetBoard());
				DisplayCurrentScore(textReversi.GetXScore(), textReversi.GetOScore());
				DisplayWhoseTurn(textReversi.GetCurrentTurn());
			}
		}

		again = AskYesOrNoQuestion("Would you like to play again?");
	}

	std::cout << "Thank you for playing! Good night!" << std::endl;
	return 0;
}