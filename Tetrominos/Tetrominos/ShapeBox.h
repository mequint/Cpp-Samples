#pragma once

#include <SFML/Graphics.hpp>
#include "Shape.h"

class ShapeBox
{
	public:
		ShapeBox();
		ShapeBox(sf::Font& font, int fontSize, sf::Vector2f position, sf::Vector2f size, std::string& title);
		
		void Draw(sf::RenderWindow& window);
		void SetShape(Shape* shape);

		sf::Vector2f GetPosition();
		
	private:
		sf::Vector2f m_position;

		sf::Text m_titleText;
		sf::RectangleShape m_rectangle;
		Shape* m_shape;
};