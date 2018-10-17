#pragma once

#include <SFML/Graphics.hpp>
#include "Shape.h"

class ShapeBox
{
	public:
		ShapeBox();
		ShapeBox(sf::Font& font, std::string& title, int fontSize);

		void SetPosition(sf::Vector2f position);
		void SetRectangle(float width, float height);

		void SetShape(Shape* shape);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Vector2f m_position;

		sf::Text m_titleText;
		sf::RectangleShape m_rectangle;
		Shape* m_shape;
};