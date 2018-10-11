#include "Shape.h"

#include <iostream> // For debug purposes, remove later

Shape::Shape(ShapeType type, Grid& grid) : m_type(type), m_grid(grid), m_hasLanded(false)
{
	const float blockSize = 16.0f;
	
	sf::Color color = m_grid.GetBlockColor(type);
	
	switch (type)
	{
		case ShapeType::I:
			std::cout << "I Block" << std::endl;

			m_origin = sf::Vector2f(2.0f, 2.0f);
			m_blocks.emplace_back(sf::Vector2i(0, 1));
			m_blocks.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(sf::Vector2i(3, 1));
			break;

		case ShapeType::J:
			std::cout << "J Block" << std::endl;

			m_origin = sf::Vector2f(1.5f, 1.5f);
			m_blocks.emplace_back(sf::Vector2i(0, 0));
			m_blocks.emplace_back(sf::Vector2i(0, 1));
			m_blocks.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(sf::Vector2i(2, 1));
			break;

		case ShapeType::L:
			std::cout << "L Block" << std::endl;

			m_origin = sf::Vector2f(1.5f, 1.5f);
			m_blocks.emplace_back(sf::Vector2i(2, 0));
			m_blocks.emplace_back(sf::Vector2i(0, 1));
			m_blocks.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(sf::Vector2i(2, 1));
			break;

		case ShapeType::O:
			std::cout << "O Block" << std::endl;

			m_origin = sf::Vector2f(1.0f, 1.0f);
			m_blocks.emplace_back(sf::Vector2i(0, 0));
			m_blocks.emplace_back(sf::Vector2i(0, 1));
			m_blocks.emplace_back(sf::Vector2i(1, 0));
			m_blocks.emplace_back(sf::Vector2i(1, 1));
			break;
		
		case ShapeType::S:
			std::cout << "S Block" << std::endl;

			m_origin = sf::Vector2f(1.5f, 1.5f);
			m_blocks.emplace_back(sf::Vector2i(1, 0));
			m_blocks.emplace_back(sf::Vector2i(2, 0));
			m_blocks.emplace_back(sf::Vector2i(0, 1));
			m_blocks.emplace_back(sf::Vector2i(1, 1));
			break;

		case ShapeType::T:
			std::cout << "T Block" << std::endl;

			m_origin = sf::Vector2f(1.5f, 1.5f);
			m_blocks.emplace_back(sf::Vector2i(1, 0));
			m_blocks.emplace_back(sf::Vector2i(0, 1));
			m_blocks.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(sf::Vector2i(2, 1));
			break;

		case ShapeType::Z:
			std::cout << "Z Block" << std::endl;

			m_origin = sf::Vector2f(1.5f, 1.5f);
			m_blocks.emplace_back(sf::Vector2i(0, 0));
			m_blocks.emplace_back(sf::Vector2i(1, 0));
			m_blocks.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(sf::Vector2i(2, 1));
			break;
	}
}

void Shape::SetPosition(int x, int y)
{
	m_position = sf::Vector2i(x, y);
}

void Shape::SetOrigin(float x, float y)
{
	m_origin.x = x;
	m_origin.y = y;
}

void Shape::SetDirection(Direction direction)
{
	m_direction = direction;

	if (direction != Direction::None)
	{
		auto boundary = m_grid.GetGridZone();

		// Block move if there is a potential collision
		for (auto block : m_blocks)
		{
			int x = m_position.x + block.x;
			int y = m_position.y + block.y;

			switch (m_direction)
			{
				case Direction::Left:
				{
					x--;

					if (x < 0 || m_grid.HasBlock(x, y))
					{
						m_direction = Direction::None;
					}
					break;
				}

				case Direction::Right:
				{
					x++;
					if (x >= m_grid.GetGridZone().width / m_grid.GetCellSize() || m_grid.HasBlock(x, y))
					{
						m_direction = Direction::None;
					}
					break;
				}

				case Direction::Up:
				{
					y--;
					if (y < 0 || m_grid.HasBlock(x, y))
					{
						m_direction = Direction::None;
					}

					break;
				}

				case Direction::Down:
				{
					y++;
					if (y >= m_grid.GetGridZone().height / m_grid.GetCellSize() || m_grid.HasBlock(x, y))
					{
						m_hasLanded = true;
						m_direction = Direction::None;
					}
					break;
				}
			}
		}
	}
}

void Shape::SetRotation(Rotation rotation)
{
	m_rotation = rotation;
}

void Shape::Update(float dt)
{
	if (m_direction != Direction::None)
	{
		switch (m_direction)
		{
			case Direction::Left:
				m_position.x -= 1;
				break;

			case Direction::Right:
				m_position.x += 1;
				break;

			case Direction::Up:
				m_position.y -= 1;
				break;

			case Direction::Down:
				m_position.y += 1;
				break;
		}
	}

	if (m_rotation == Rotation::CW)
	{
		for (auto& block : m_blocks)
		{
			int temp = block.x;
			block.x = block.y;
			block.y = temp;
		}
	}
	else if (m_rotation == Rotation::CCW)
	{
		for (auto& block : m_blocks)
		{
			int temp = block.x;
			block.x = block.y;
			block.y = temp;
		}
	}

	//for (auto& block : m_blocks)
	//{
	//	if (m_rotation != Rotation::None)
	//	{
	//		// Screen to Local Space
	//		float localX = m_position.x - block.GetPosition().x + m_origin.x;
	//		float localY = m_position.y - block.GetPosition().y + m_origin.y;

	//		float x1 = -localY;
	//		float y1 = localX;

	//		float newX = -localY + m_position.x + m_origin.x;
	//		float newY = localX + m_position.y + m_origin.y;
	//		block.SetPosition(newX, newY);
	//		
	//		/*
	//		block.SetPosition(block.GetPosition().x + m_position.x + m_origin.x,
	//			block.GetPosition().y + m_position.y + m_origin.y);
	//		*/

	//		/*
	//		std::cout <<
	//			"(" << block.GetPosition().x << "," << block.GetPosition().y << ") -> " <<
	//			"(" << localX << "," << localY << ")" << std::endl;
	//		*/
	//	}
	//}

	//if (m_rotation != Rotation::None)
	//	std::cout << std::endl;

	SetRotation(Rotation::None);
	SetDirection(Direction::None);
}

void Shape::Draw(sf::RenderWindow& window)
{
	auto gridZone = m_grid.GetGridZone();
	int cellSize = m_grid.GetCellSize();

	auto cell = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
	for (auto block : m_blocks)
	{
		sf::Color color = m_grid.GetBlockColor(m_type);
		cell.setFillColor(color);

		sf::Color outlineColor = color;
		outlineColor.r = 3 * outlineColor.r / 5;
		outlineColor.g = 3 * outlineColor.g / 5;
		outlineColor.b = 3 * outlineColor.b / 5;
		cell.setOutlineColor(outlineColor);

		cell.setOutlineThickness(-1.0f);
		cell.setPosition(
			gridZone.left + (m_position.x + block.x) * cellSize,
			gridZone.top + (m_position.y + block.y) * cellSize);

		window.draw(cell);
	}
}

bool Shape::HasLanded() const
{
	return m_hasLanded;
}

std::vector<sf::Vector2i> Shape::GetBlocks()
{
	return m_blocks;
}

sf::Vector2i Shape::GetPosition()
{
	return m_position;
}

ShapeType Shape::GetType()
{
	return m_type;
}