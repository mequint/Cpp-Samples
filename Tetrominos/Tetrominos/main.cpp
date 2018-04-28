// GLAD must be on top - otherwise GLFW will throw a fit
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ConfigurationManager.h"
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

	return 0;
}