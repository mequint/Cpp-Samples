#include <SFML/Graphics.hpp>

#include "Game.h"

#include "Block.h"
#include "Grid.h"
#include "Random.h"
#include "Shape.h"

int main()
{
	/*
	Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Draw();
		game.PostProcess();
	}
	*/

	const int windowWidth = 800;
	const int windowHeight = 600;

	const int blockSize = 16;

	int startPosX = windowWidth / 2 - 5 * blockSize;
	int startPosY = windowHeight / 2 - 10 * blockSize;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetrominos");

	Grid grid(10, 20, startPosX, startPosY, blockSize);
	grid.ToggleVisibility();

	Random rng;
	Shape lander(ShapeType(rng.GetInt(0,6)), grid.GetGridZone());
	lander.SetPosition((float)startPosX, (float)startPosY);

	std::vector<Block> blocks;

	bool spawnNewTetrimino = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				lander.SetDirection(Direction::Left);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				lander.SetDirection(Direction::Right);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				lander.SetDirection(Direction::Up);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				lander.SetDirection(Direction::Down);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				grid.ToggleVisibility();
			}
		}

		if (lander.HasLanded())
		{
			for (auto block : lander.GetBlocks())
			{
				grid.AddBlock(block);
			}
			lander = Shape(ShapeType(rng.GetInt(0, 6)), grid.GetGridZone());
			lander.SetPosition((float)startPosX, (float)startPosY);
			spawnNewTetrimino = false;
		}

		lander.Update(0.0f);

		window.clear(sf::Color::Black);
		grid.Draw(window);
		lander.Draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}