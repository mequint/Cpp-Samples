#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Board.h"
#include "Display.h"
#include "Input.h"
#include "Piece.h"
#include "Player.h"

// TODO:
//		Make a game class to hold the game specific variables
//		AI! 
//			*Add a method Board->AvailableMoves as a vector of moves
//			*Have the AI player make a random move based on the moves available
//			*Use backtracking and weighted decision making for the AI to try for the maximum available pieces in a turn
//			*Make the AI smarter by using a heuristic of key placements on the game board
//		Make the TextReversi follow a state based pattern which accesses a "global" game class
//			* Intro state
//			* Main Menu state
//			* New Game state
//			* Load Game state
//			* Display Rules state
//			* Game state
//			* GameOver state
//			* Exiting state
//		2.0 - Make the game multiplayer by using Sockets
//		3.0 - 2D or 3D Graphical representation!

void SaveGame(const std::string& name, const Board& board, Piece currentTurn, Player& player1, Player& player2)
{
	std::ofstream myFile;
	myFile.open(name);

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			myFile << PieceToChar(board.GetCell(i, j));
		}
		myFile << std::endl;
	}

	myFile << PieceToChar(currentTurn) << std::endl;
	myFile << PieceToChar(player1.piece) << " " << player1.isHuman << std::endl;
	myFile << PieceToChar(player2.piece) << " " << player2.isHuman << std::endl;
}

void LoadGame(const std::string& filename, Board& board, int& totalMoves, Piece& currentTurn, Player& player1, Player& player2)
{
	std::ifstream myFile;
	myFile.open(filename);

	if (myFile.is_open())
	{
		// Reset total moves - count this while loading the board
		totalMoves = 0;

		// Load the board
		for (int i = 0; i < 8; ++i)
		{
			std::string line;
			getline(myFile, line);

			for (int j = 0; j < 8; ++j)
			{
				board.SetCell(i, j, CharToPiece(line[j]));
				totalMoves++;
			}
		}

		// Load the current turn
		char c;
		myFile >> c;
		currentTurn = CharToPiece(c);

		// Load player 1
		bool isHuman;
		myFile >> c >> isHuman;
		player1.piece = CharToPiece(c);
		player1.isHuman = isHuman;

		// Load player 2
		myFile >> c >> isHuman;
		player2.piece = CharToPiece(c);
		player2.isHuman = isHuman;
	}
	else
	{
		std::cout << "ERROR: Failed to load game /'" << filename << "/'";
	}
}

int main()
{
	int totalMoves = 4;
	char again = 'y';

	DisplayInstructions();

	while (again == 'y')
	{
		Board board;

		// determine who gets to play the piece
		Player player1;
		player1.piece = GetPlayerPiece();
		player1.isHuman = true;

		Player player2;
		player2.piece = OppositePiece(player1.piece);
		player2.isHuman = true;

		Piece currentTurn = Piece::X;
		DisplayBoard(board);
		DisplayCurrentScore(board, player1.piece, player2.piece, totalMoves);
		DisplayWhoseTurn(currentTurn);

		bool gameOver = false;
		while (!gameOver)
		{
			bool movesAvailableLastTurn = true;

			if (board.AreMovesAvailable(currentTurn))
			{
				std::string filename;
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
						DisplayCurrentScore(board, player1.piece, player2.piece, totalMoves);

						DisplayWhoseTurn(currentTurn);

						break;

					case Command::Save:
						std::cout << "Saving game" << std::endl;

						std::cout << "Enter a save name: ";
						getline(std::cin, filename);

						SaveGame(filename, board, currentTurn, player1, player2);
						break;

					case Command::Load:
						std::cout << "Loading game" << std::endl;

						std::cout << "Enter a game name to load: ";
						getline(std::cin, filename);

						LoadGame(filename, board, totalMoves, currentTurn, player1, player2);

						break;

					case Command::Quit:
						gameOver = true;
						break;

					case Command::PrintBoard:
						DisplayBoard(board);
						DisplayCurrentScore(board, player1.piece, player2.piece, totalMoves);
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
				DisplayCurrentScore(board, player1.piece, player2.piece, totalMoves);

				DisplayWhoseTurn(currentTurn);
			}
		}

		again = AskYesOrNoQuestion("Would you like to play again?");
	}

	std::cout << "Thank you for playing! Good night!" << std::endl;
	return 0;
}