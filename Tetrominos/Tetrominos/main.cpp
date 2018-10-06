#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Grid.h"
#include "Shape.h"

int main()
{
	const int windowWidth = 800;
	const int windowHeight = 600;

	const int blockSize = 16;

	int startPosX = windowWidth / 2 - 5 * blockSize;
	int startPosY = windowHeight / 2 - 10 * blockSize;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetrominos");

	Grid grid(10, 20, startPosX, startPosY, blockSize);

	std::vector<Shape> shapes;
	for (int i = 0; i < 7; ++i)
	{
		shapes.push_back(ShapeType(i));
	}
	
	shapes[0].SetPosition((float)startPosX, (float)startPosY);
	shapes[1].SetPosition((float)startPosX + blockSize * 4, (float)startPosY);
	shapes[2].SetPosition((float)startPosX + blockSize * 8, (float)startPosY);
	shapes[3].SetPosition((float)startPosX + blockSize * 12, (float)startPosY);
	shapes[4].SetPosition((float)startPosX + blockSize * 2, (float)startPosY + blockSize * 4);
	shapes[5].SetPosition((float)startPosX + blockSize * 6, (float)startPosY + blockSize * 4);
	shapes[6].SetPosition((float)startPosX + blockSize * 10, (float)startPosY + blockSize * 4);

	std::vector<Block> blocks;
	for (int i = 1; i < 7; ++i)
	{
		for (auto block : shapes[i].GetBlocks())
		{
			blocks.emplace_back(block);
		}
	}

	//Block block(blockSize);
	//block.SetPosition(startPosX, startPosY);
	//block.SetColor(sf::Color::Red);

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
				shapes[0].SetDirection(Direction::Left);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				shapes[0].SetDirection(Direction::Right);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				shapes[0].SetDirection(Direction::Up);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				shapes[0].SetDirection(Direction::Down);
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

		shapes[0].Collides(blocks, grid.GetGridZone());

		shapes[0].Update(0.0f);

		if (shapes[0].GetCollides())
		{
			window.clear(sf::Color::Red);
		}
		else
		{
			window.clear(sf::Color::Black);
		}

		grid.Draw(window);

		for (int i = 0; i < 7; ++i)
		{
			shapes[i].Draw(window);
		}
		window.display();
	}

	return EXIT_SUCCESS;
}