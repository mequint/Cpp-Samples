#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	
	Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Draw();
		game.PostProcess();
	}

	return EXIT_SUCCESS;
}