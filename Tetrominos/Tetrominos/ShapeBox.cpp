#include "ShapeBox.h"

ShapeBox::ShapeBox() : m_shape(nullptr) {}

ShapeBox::ShapeBox(sf::Font& font, int fontSize, sf::Vector2f position, sf::Vector2f size, std::string& title) : 
	m_shape(nullptr)
{	
	m_rectangle.setPosition(position);
	m_rectangle.setSize(size);
	m_rectangle.setFillColor(sf::Color::Transparent);
	m_rectangle.setOutlineColor(sf::Color::White);
	m_rectangle.setOutlineThickness(-1.0f);

	m_titleText.setFont(font);
	m_titleText.setCharacterSize(fontSize);
	m_titleText.setString(title);
	m_titleText.setFillColor(sf::Color::White);
	
	sf::Vector2f textCenter = sf::Vector2f(m_titleText.getLocalBounds().width / 2.0f, 0.0f);
	sf::Vector2f rectTopCenter = sf::Vector2f(m_rectangle.getSize().x / 2.0f, 0.0f);
	m_titleText.setPosition(position + rectTopCenter - textCenter);
}

void ShapeBox::SetShape(Shape* shape)
{
	m_shape = shape;
	float size = m_shape->GetBlockSize();
	sf::Vector2f boxCenter = m_rectangle.getSize() / 2.0f;
	
	sf::Vector2f shapeCenter;
	switch (m_shape->GetType())
	{
		case ShapeType::I:
			shapeCenter = sf::Vector2f(2.0f * size, 1.0f * size);
			break;

		case ShapeType::J:
		case ShapeType::L:
		case ShapeType::S:
		case ShapeType::T:
		case ShapeType::Z:
			shapeCenter = sf::Vector2f(1.5f * size, 0.5f * size);
			break;

		case ShapeType::O:
			shapeCenter = sf::Vector2f(1.0f * size, 0.5f * size);
			break;
	}

	m_shape->SetReferencePoint(m_rectangle.getPosition() + boxCenter - shapeCenter);
}

sf::Vector2f ShapeBox::GetPosition()
{
	return m_rectangle.getPosition();
}

void ShapeBox::Draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
	window.draw(m_titleText);
	if (m_shape == nullptr) return;

	m_shape->Draw(window);
}