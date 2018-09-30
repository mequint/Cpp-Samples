#include "Block.h"

Block::Block(float blockSize) : m_rectShape(sf::Vector2f(blockSize, blockSize))
{
}

void Block::Draw(sf::RenderWindow & window)
{
	window.draw(m_rectShape);
}

void Block::SetPosition(float x, float y)
{
	m_rectShape.setPosition(x, y);
}

void Block::SetColor(sf::Color color)
{
	m_color = color;
	m_rectShape.setFillColor(m_color);
	m_rectShape.setOutlineThickness(-1.0f);

	auto outlineColor = m_color;
	outlineColor.r = 3 * outlineColor.r / 5;
	outlineColor.g = 3 * outlineColor.g / 5;
	outlineColor.b = 3 * outlineColor.b / 5;
	m_rectShape.setOutlineColor(outlineColor);
}

sf::Vector2f Block::GetPosition()
{
	return m_rectShape.getPosition();
}