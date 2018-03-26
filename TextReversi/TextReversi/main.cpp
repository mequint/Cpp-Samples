#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Board.h"
#include "Display.h"
#include "Input.h"
#include "Piece.h"

// TODO:
//		Add easy exiting operations via command line
//		Make a game class to hold the game specific variables
//		STEP (MAYBE): Make the TextReversi follow a state based pattern which accesses the "global" game class
//			* Intro state
//			* Setup state
//			* Game state
//			* GameOver state
//		2.0 - 2D or 3D Graphical representation!

// Bugs (to fix):
//		Replace input with a getline call and parse out the 2 values manually to prevent invalid values
//		In the flip pieces method make sure that the col values aren't causing the next index to move one row up or down (erroneous behavior)
//			*Consider replacing the Vector with a 2D Vector - this will change our board implementation

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

		while (totalMoves < 64)
		{
			int move = GetPlayerMove(board, currentTurn);
			board.MakeMove(move, currentTurn);
		
			totalMoves++;
			currentTurn = OppositePiece(currentTurn);

			DisplayBoard(board);
			DisplayCurrentScore(board, player1, player2, totalMoves);
			
			DisplayWhoseTurn(currentTurn);
		}

		DisplayCurrentScore(board, player1, player2, totalMoves);

		again = AskYesOrNoQuestion("Would you like to play again?");
	}

	std::cout << "Thank you for playing! Good night!" << std::endl;
	return 0;
}