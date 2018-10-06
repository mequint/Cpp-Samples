#include "Block.h"

Block::Block(float blockSize) : m_rectShape(sf::Vector2f(blockSize, blockSize)),
	m_AABB(0, 0, blockSize, blockSize), m_blockSize(blockSize)
{
}

void Block::Draw(sf::RenderWindow & window)
{
	window.draw(m_rectShape);
}

void Block::Update(float dt)
{
	switch (m_direction)
	{
		case Direction::Up:
			m_position += sf::Vector2f(0.0f, -m_blockSize);
			break;
		case Direction::Down:
			m_position += sf::Vector2f(0.0f, m_blockSize);
			break;
		case Direction::Left:
			m_position += sf::Vector2f(-m_blockSize, 0.0f);
			break;
		case Direction::Right:
			m_position += sf::Vector2f(m_blockSize, 0.0f);
			break;
	}

	m_direction = Direction::None;

	UpdateRectShape();
	UpdateAABB();
}

void Block::SetPosition(sf::Vector2f position)
{
	m_position = position;
	UpdateRectShape();
	UpdateAABB();
}

void Block::SetPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y); 
	UpdateRectShape();
	UpdateAABB();
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

void Block::SetDirection(Direction direction)
{
	m_direction = direction;
}

sf::Vector2f Block::GetPosition()
{
	return m_position;
}

float Block::GetSize() const
{
	return m_blockSize;
}

sf::FloatRect Block::GetAABB()
{
	return m_AABB;
}

void Block::UpdateAABB()
{
	m_AABB.left = m_position.x;
	m_AABB.top = m_position.y;
}

void Block::UpdateRectShape()
{
	m_rectShape.setPosition(m_position);
}