#include <SFML/Graphics.hpp>

#include "Game.h"

#include "Grid.h"
#include "RandomGenerator.h"
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

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetrominos");

	// Grid 
	int startPosX = windowWidth / 2 - 5 * blockSize;
	int startPosY = windowHeight / 2 - 10 * blockSize;
	Grid grid(10, 20, startPosX, startPosY, blockSize);
	grid.ToggleVisibility();

	RandomGenerator randomGenerator((int)ShapeType::Z);

	// Lander
	int spawnX = 5;
	int spawnY = 2;

	Shape lander(ShapeType(randomGenerator.GetNextInt()), grid);
	lander.SetPosition(spawnX, spawnY);

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
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
			{
				lander.SetRotation(Rotation::CCW);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
			{
				lander.SetRotation(Rotation::CW);
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
			sf::Vector2i landerPos = lander.GetPosition();
			for (auto block : lander.GetBlocks())
			{
				int col = block.x + landerPos.x;
				int row = block.y + landerPos.y;
				int type = static_cast<int>(lander.GetType());

				grid.AddBlock(col, row, type);
			}

			lander = Shape(ShapeType(randomGenerator.GetNextInt()), grid);
			lander.SetPosition(spawnX, spawnY);
		}

		lander.Update(0.0f);

		window.clear(sf::Color::Black);
		grid.Draw(window);
		lander.Draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}