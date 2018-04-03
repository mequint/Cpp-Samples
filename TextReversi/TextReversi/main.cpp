#include "Game.h"

int main()
{
	Game game;
	while (game.IsRunning())
	{
		game.Run();
	}

	return 0;
}