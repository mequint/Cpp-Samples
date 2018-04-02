#include "Game.h"

// TODO:
//		AI! 
//			*Add a game logger to track moves
//			*Have the AI player make a random move based on the moves available
//			*Use backtracking and weighted decision making for the AI to try for the maximum available pieces in a turn (Min Max)
//			*Make the AI smarter by using a heuristic of key placements on the game board
//		Machine Learning
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