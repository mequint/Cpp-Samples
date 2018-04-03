#include "Game.h"

// TODO:
//		AI! 
//			*Use backtracking and weighted decision making for the AI to try for the maximum available pieces in a turn (MinMax)
//			*Make the AI smarter by using a heuristic of key placements on the game board
//			*Add a game logger to track moves
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