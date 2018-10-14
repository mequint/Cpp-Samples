#include <SFML/Graphics.hpp>

#include "Game.h"

#include "Grid.h"
#include "RandomGenerator.h"
#include "Shape.h"

#include <iostream>

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

	sf::Clock clock;
	sf::Time elapsedTime = clock.restart();

	float currentFallTime = 0.0f;
	float nextFallTime = 1.0f;

	int lines = 0;
	int speedUp = 10;

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

		currentFallTime += elapsedTime.asSeconds();
		if (currentFallTime >= nextFallTime)
		{
			currentFallTime = 0.0f;
			lander.SetDirection(Direction::Down);
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

			int score = grid.RemoveCompleteLines();
			lines += score;

			if (lines > speedUp)
			{
				nextFallTime -= 0.1f;

				speedUp += 10;
				std::cout << "Speed Up!" << std::endl;
			}

			std::cout << "Points: " << score << " Lines: " << lines << std::endl;
			lander = Shape(ShapeType(randomGenerator.GetNextInt()), grid);
			lander.SetPosition(spawnX, spawnY);
		}

		lander.Update(elapsedTime.asSeconds());

		window.clear(sf::Color::Black);
		grid.Draw(window);
		lander.Draw(window);
		window.display();

		elapsedTime = clock.restart();
	}

	return EXIT_SUCCESS;
}