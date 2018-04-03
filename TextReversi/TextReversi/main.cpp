#include "Game.h"

// TODO:
//		AI! 
//			*Use backtracking and weighted decision making for the AI to maximize future moves for self and minimize opponent moves
//			*Add AI difficulty option (Easy - doesn't use the corner heuristic, Medium - uses the corner heurestic, Hard - uses movement potential calculation to limit player moves)
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