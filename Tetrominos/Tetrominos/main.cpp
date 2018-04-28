#include <GL/glew.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	ConfigurationManager config;
	config.Load("assets/settings.txt");

	Game game(config);
	if (game.Initialize())
	{
		while (!game.GetWindow()->IsDone())
		{
			game.Update();
			game.Render();
		}
	}

	game.Cleanup();

	return EXIT_SUCCESS;
}