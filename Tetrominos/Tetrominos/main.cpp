#include <GL/glew.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

// Bug: Fullscreen mode switches to fullscreen and deletes all the screen data, then switches back to windowed mode...

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
			game.PostProcessing();
		}
	}

	return EXIT_SUCCESS;
}