#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Board.h"
#include "Display.h"
#include "Input.h"
#include "Piece.h"

// TODO:
//		When moves are unavailable for a player, switch the turn to the opponent
//			* Requires a new board method, MovesAvailable - return bool for now but AI will require an int
//		Add easy exiting operations via command line
//		Add a save function to command line to save the state of the game
//		Add a load function to load a previously saved state
//		AI! 
//			*Have the AI player make a random move based on the moves available
//			*Use backtracking and weighted decision making for the AI to try for the maximum available pieces in a turn
//			*Make the AI smarter by using a heuristic of key placements on the game board
//		STEP (MAYBE): Make a game class to hold the game specific variables
//		STEP (MAYBE): Make the TextReversi follow a state based pattern which accesses the "global" game class
//			* Intro state
//			* Setup state
//			* Game state
//			* GameOver state
//		2.0 - Make the game multiplayer by using Sockets
//		3.0 - 2D or 3D Graphical representation!

// Bugs (to fix):
//		Replace input with a getline call and parse out the 2 values manually to prevent invalid values

int main()
{
	int totalMoves = 4;
	char again = 'y';

	DisplayInstructions();

	while (again == 'y')
	{
		Board board;

		// determine who gets to play the piece
		Piece player1 = GetPlayerPiece();
		Piece player2 = OppositePiece(player1);

		Piece currentTurn = Piece::X;
		DisplayBoard(board);
		DisplayCurrentScore(board, player1, player2, totalMoves);
		DisplayWhoseTurn(currentTurn);

		bool gameOver = false;
		while (!gameOver)
		{
			bool movesAvailableLastTurn = true;

			if (board.AreMovesAvailable(currentTurn))
			{
				Move move = GetPlayerMove(board, currentTurn);
				switch (move.Command)
				{
					case Command::Move:
						board.MakeMove(move.Row, move.Col, currentTurn);

						totalMoves++;
						movesAvailableLastTurn = true;

						if (totalMoves == 64)
							gameOver = true;

						currentTurn = OppositePiece(currentTurn);

						DisplayBoard(board);
						DisplayCurrentScore(board, player1, player2, totalMoves);

						DisplayWhoseTurn(currentTurn);

						break;

					case Command::Save:
						std::cout << "Saving game (stub)\n";
						break;

					case Command::Load:
						std::cout << "Loading game (stub)\n";
						break;

					case Command::Quit:
						gameOver = true;
						break;

					case Command::PrintBoard:
						DisplayBoard(board);
						DisplayCurrentScore(board, player1, player2, totalMoves);
						DisplayWhoseTurn(currentTurn);
						break;

					case Command::Options:
						std::cout << "[a-h][1-8]:   Make a move\n";
						std::cout << "save [str]:   Save the game\n";
						std::cout << "load [str]:   Load a saved game\n";
						std::cout << "quit:         Exit the game\n";
						std::cout << "board:        Print the board\n";
						std::cout << "options:      Display a list of options\n" << std::endl;

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

				currentTurn = OppositePiece(currentTurn);

				DisplayBoard(board);
				DisplayCurrentScore(board, player1, player2, totalMoves);

				DisplayWhoseTurn(currentTurn);
			}
		}

		again = AskYesOrNoQuestion("Would you like to play again?");
	}

	std::cout << "Thank you for playing! Good night!" << std::endl;
	return 0;
}