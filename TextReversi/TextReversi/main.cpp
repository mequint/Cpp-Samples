#include "Game.h"

// TODO:
//		AI! 
//			*Add a method Board->AvailableMoves as a vector of moves
//			*Use the Board->AvailableMoves as a move helper to help players know what moves are available
//			*Have the AI player make a random move based on the moves available
//			*Use backtracking and weighted decision making for the AI to try for the maximum available pieces in a turn
//			*Make the AI smarter by using a heuristic of key placements on the game board
//		Machine Learning
//			*Add a game logger to track AI moves
//			*Figure out how teach the computer how to play Reversi
//		2.0 - Make the game multiplayer by using Sockets
//		3.0 - 2D or 3D Graphical representation!

int main()
{
	Game game;
	while (game.IsRunning())
	{
		game.Run();
	}

	return 0;
}