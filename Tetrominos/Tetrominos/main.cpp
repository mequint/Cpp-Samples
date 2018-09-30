#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Grid.h"
#include "Tetromino.h"

int main()
{
	const int windowWidth = 800;
	const int windowHeight = 600;

	const int blockSize = 16;

	int startPosX = windowWidth / 2 - 5 * blockSize;
	int startPosY = windowHeight / 2 - 10 * blockSize;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetrominos");

	Grid grid(10, 20, startPosX, startPosY, blockSize);

	std::vector<Tetromino> tetrominos;
	for (int i = 0; i < 7; ++i)
	{
		tetrominos.push_back(TetrominoType(i));
	}
	
	tetrominos[0].SetPosition((float)startPosX, (float)startPosY);
	tetrominos[1].SetPosition((float)startPosX + blockSize * 4, (float)startPosY);
	tetrominos[2].SetPosition((float)startPosX + blockSize * 8, (float)startPosY);
	tetrominos[3].SetPosition((float)startPosX + blockSize * 12, (float)startPosY);
	tetrominos[4].SetPosition((float)startPosX + blockSize * 2, (float)startPosY + blockSize * 4);
	tetrominos[5].SetPosition((float)startPosX + blockSize * 6, (float)startPosY + blockSize * 4);
	tetrominos[6].SetPosition((float)startPosX + blockSize * 10, (float)startPosY + blockSize * 4);

	Block block(blockSize);
	block.SetPosition(startPosX, startPosY);
	block.SetColor(sf::Color::Red);

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
				tetrominos[0].Move(Direction::Left);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				tetrominos[0].Move(Direction::Right);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				tetrominos[0].Move(Direction::Up);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				tetrominos[0].Move(Direction::Down);
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

		window.clear(sf::Color::Black);

		grid.Draw(window);

		for (int i = 0; i < tetrominos.size(); ++i)
		{
			tetrominos[i].Draw(window);
		}
		
		window.display();
	}

	return EXIT_SUCCESS;
}