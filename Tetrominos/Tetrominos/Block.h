#pragma once

#include <SFML/Graphics.hpp>

#include "Direction.h"

class Block
{
	public:
		Block(float blockSize);

		void Draw(sf::RenderWindow& window);

		void SetPosition(float x, float y);
		void SetColor(sf::Color color);

		sf::Vector2f GetPosition();

	private:
		sf::Color m_color;

		sf::RectangleShape m_rectShape;
};