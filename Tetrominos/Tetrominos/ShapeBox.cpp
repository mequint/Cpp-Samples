#include "ShapeBox.h"

ShapeBox::ShapeBox() {}

ShapeBox::ShapeBox(sf::Font& font, std::string& title, int fontSize) 
{
	m_titleText.setFont(font);
	m_titleText.setCharacterSize(fontSize);
	m_titleText.setString(title);
	m_titleText.setFillColor(sf::Color::White);

	m_rectangle.setFillColor(sf::Color::Transparent);
	m_rectangle.setOutlineColor(sf::Color::White);
	m_rectangle.setOutlineThickness(-1.0f);
}

void ShapeBox::SetPosition(sf::Vector2f position)
{
	m_position = position;
	m_titleText.setPosition(position);
	m_rectangle.setPosition(position);
}

void ShapeBox::SetRectangle(float width, float height)
{
	m_rectangle.setSize(sf::Vector2f(width, height));
}

void ShapeBox::SetShape(Shape* shape)
{
	m_shape = shape;
}

void ShapeBox::Draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
	window.draw(m_titleText);
	if (m_shape == nullptr) return;
}
