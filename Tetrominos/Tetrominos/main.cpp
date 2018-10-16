#include <SFML/Graphics.hpp>

#include "Game.h"

#include "Grid.h"
#include "RandomGenerator.h"
#include "Shape.h"

#include <iostream>

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