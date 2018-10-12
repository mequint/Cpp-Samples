#include "Shape.h"

#include <iostream> // For debug purposes, remove later

Shape::Shape(ShapeType type, Grid& grid) : m_type(type), m_grid(grid), m_hasLanded(false), m_rotationIndex(0)
{
	const float blockSize = 16.0f;
	
	sf::Color color = m_grid.GetBlockColor(type);
	
	switch (type)
	{
		case ShapeType::I:
		{
			std::cout << "I Block" << std::endl;

			Block block1;
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			block1.emplace_back(sf::Vector2i(3, 1));
			m_blocks.emplace_back(block1);

			Block block2;
			block2.emplace_back(sf::Vector2i(2, 0));
			block2.emplace_back(sf::Vector2i(2, 1));
			block2.emplace_back(sf::Vector2i(2, 2));
			block2.emplace_back(sf::Vector2i(2, 3));
			m_blocks.emplace_back(block2);

			Block block3;
			block3.emplace_back(sf::Vector2i(0, 2));
			block3.emplace_back(sf::Vector2i(1, 2));
			block3.emplace_back(sf::Vector2i(2, 2));
			block3.emplace_back(sf::Vector2i(3, 2));
			m_blocks.emplace_back(block3);

			Block block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			block4.emplace_back(sf::Vector2i(1, 3));
			m_blocks.emplace_back(block4);

			break;
		}

		case ShapeType::J:
		{
			std::cout << "J Block" << std::endl;

			Block block1;
			block1.emplace_back(sf::Vector2i(0, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block1);

			Block block2;
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(2, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block2);

			Block block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			block3.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block3);

			Block block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			block4.emplace_back(sf::Vector2i(0, 2));
			m_blocks.emplace_back(block4);

			break;
		}

		case ShapeType::L:
		{
			std::cout << "L Block" << std::endl;

			Block block1;
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			block1.emplace_back(sf::Vector2i(2, 0));
			m_blocks.emplace_back(block1);

			Block block2;
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			block2.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block2);

			Block block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(0, 2));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block3);

			Block block4;
			block4.emplace_back(sf::Vector2i(0, 0));
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block4);

			break;
		}

		case ShapeType::O:
		{
			std::cout << "O Block" << std::endl;

			Block block1;
			block1.emplace_back(sf::Vector2i(0, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block1);

			Block block2;
			block2.emplace_back(sf::Vector2i(0, 0));
			block2.emplace_back(sf::Vector2i(0, 1));
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block2);

			Block block3;
			block3.emplace_back(sf::Vector2i(0, 0));
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 0));
			block3.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block3);

			Block block4;
			block4.emplace_back(sf::Vector2i(0, 0));
			block4.emplace_back(sf::Vector2i(0, 1));
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block4);

			break;
		}

		case ShapeType::S:
		{
			std::cout << "S Block" << std::endl;

			Block block1;
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(2, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block1);

			Block block2;
			block2.emplace_back(sf::Vector2i(0, 0));
			block2.emplace_back(sf::Vector2i(0, 1));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block2);

			Block block3;
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			block3.emplace_back(sf::Vector2i(0, 2));
			block3.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block3);

			Block block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(2, 1));
			block4.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block4);

			break;
		}

		case ShapeType::T:
		{
			std::cout << "T Block" << std::endl;

			Block block1;
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block1);

			Block block2;
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			block2.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block2);

			Block block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			block3.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block3);

			Block block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(0, 1));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block4);

			break;
		}

		case ShapeType::Z:
		{
			std::cout << "Z Block" << std::endl;

			Block block1;
			block1.emplace_back(sf::Vector2i(0, 0));
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block1);

			Block block2;
			block2.emplace_back(sf::Vector2i(2, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(2, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block2);

			Block block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(1, 2));
			block3.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block3);

			Block block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(0, 1));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(0, 2));
			m_blocks.emplace_back(block4);

			break;
		}

	}
}

void Shape::SetPosition(int x, int y)
{
	m_position = sf::Vector2i(x, y);
}

void Shape::SetDirection(Direction direction)
{
	m_direction = direction;

	if (direction != Direction::None)
	{
		auto boundary = m_grid.GetGridZone();

		// Block move if there is a potential collision
		for (auto block : m_blocks[m_rotationIndex])
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
						return;
					}
					break;
				}

				case Direction::Right:
				{
					x++;
					if (x >= m_grid.GetGridZone().width / m_grid.GetCellSize() || m_grid.HasBlock(x, y))
					{
						m_direction = Direction::None;
						return;
					}
					break;
				}

				case Direction::Up:
				{
					y--;
					if (y < 0 || m_grid.HasBlock(x, y))
					{
						m_direction = Direction::None;
						return;
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
						return;
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

	if (m_rotation != Rotation::None)
	{
		Block shape;
		if (m_rotation == Rotation::CW)
		{
			int index = m_rotationIndex - 1;
			if (index < 0)
			{
				index = 3;
			}

			shape = m_blocks[index];
		}
		else if (m_rotation == Rotation::CCW)
		{
			int index = m_rotationIndex + 1;
			if (index > 3)
			{
				index = 0;
			}

			shape = m_blocks[index];
		}

		for (auto block : shape)
		{
			int x = m_position.x + block.x;
			int y = m_position.y + block.y;

			bool outOfBounds = x < 0 || x >= m_grid.GetGridZone().width / m_grid.GetCellSize() ||
				y < 0 || y >= m_grid.GetGridZone().height / m_grid.GetCellSize();

			if (outOfBounds || m_grid.HasBlock(block.x, block.y))
			{
				m_rotation = Rotation::None;
				return;
			}
		}
	}
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
		if (m_rotationIndex == 3)
		{
			m_rotationIndex = 0;
		}
		else
		{
			m_rotationIndex++;
		}
	}
	else if (m_rotation == Rotation::CCW)
	{
		if (m_rotationIndex == 0)
		{
			m_rotationIndex = 3;
		}
		else
		{
			m_rotationIndex--;
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
	for (auto block : m_blocks[m_rotationIndex])
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
	return m_blocks[m_rotationIndex];
}

sf::Vector2i Shape::GetPosition()
{
	return m_position;
}

ShapeType Shape::GetType()
{
	return m_type;
}