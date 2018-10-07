#include "Shape.h"

#include <iostream> // For debug purposes, remove later

Shape::Shape(ShapeType type, Grid& grid) : m_hasLanded(false), m_grid(grid)
{
	const float blockSize = 16.0f;
	const std::unordered_map<ShapeType, sf::Color> TetrominoColors
	{
		{ ShapeType::I, sf::Color::Red },
		{ ShapeType::J, sf::Color::Blue },
		{ ShapeType::L, sf::Color::Green },
		{ ShapeType::O, sf::Color::White },
		{ ShapeType::S, sf::Color::Cyan },
		{ ShapeType::T, sf::Color::Magenta },
		{ ShapeType::Z, sf::Color::Yellow }
	};

	sf::Color color = TetrominoColors.find(type)->second;		// Should perform a check...but this should also be in a factory

	for (int i = 0; i < 4; ++i)
	{
		m_blocks.emplace_back(blockSize);
	}
	
	switch (type)
	{
		case ShapeType::I:
			m_position = sf::Vector2f(0.0f, 0.0f);
			
			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(color);
			m_blocks[2].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[2].SetColor(color);
			m_blocks[3].SetPosition(0.0f, blockSize * 3.0f);
			m_blocks[3].SetColor(color);
		break;

		case ShapeType::J:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(blockSize, 0.0f);
			m_blocks[0].SetColor(color);
			m_blocks[1].SetPosition(blockSize, blockSize);
			m_blocks[1].SetColor(color);
			m_blocks[2].SetPosition(blockSize, blockSize * 2.0f);
			m_blocks[2].SetColor(color);
			m_blocks[3].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[3].SetColor(color);
		break;

		case ShapeType::L:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(color);
			m_blocks[2].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[2].SetColor(color);
			m_blocks[3].SetPosition(blockSize, blockSize * 2.0f);
			m_blocks[3].SetColor(color);
		break;

		case ShapeType::O:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(color);
			m_blocks[2].SetPosition(blockSize, 0.0f);
			m_blocks[2].SetColor(color);
			m_blocks[3].SetPosition(blockSize, blockSize);
			m_blocks[3].SetColor(color);
		break;

		case ShapeType::S:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(color);
			m_blocks[2].SetPosition(blockSize, blockSize);
			m_blocks[2].SetColor(color);
			m_blocks[3].SetPosition(blockSize, blockSize * 2.0f);
			m_blocks[3].SetColor(color);
		break;

		case ShapeType::T:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(color);
			m_blocks[1].SetPosition(blockSize, 0.0f);
			m_blocks[1].SetColor(color);
			m_blocks[2].SetPosition(blockSize * 2.0f, 0.0f);
			m_blocks[2].SetColor(color);
			m_blocks[3].SetPosition(blockSize, blockSize);
			m_blocks[3].SetColor(color);
		break;

		case ShapeType::Z:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(blockSize, 0.0f);
			m_blocks[0].SetColor(color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(color);
			m_blocks[2].SetPosition(blockSize, blockSize);
			m_blocks[2].SetColor(color);
			m_blocks[3].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[3].SetColor(color);
		break;
	}
}

void Shape::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	for (auto& block : m_blocks)
	{
		sf::Vector2f newPosition(block.GetPosition() + m_position);
		block.SetPosition(newPosition);
	}
}

void Shape::SetDirection(Direction direction)
{
	if (direction != Direction::None)
	{
		auto boundary = m_grid.GetGridZone();
		m_direction = direction;

		// Block move if there is a potential collision
		for (auto block : m_blocks)
		{
			float nextPosX, nextPosY;
			int col, row;

			switch (m_direction)
			{
				case Direction::Left:
					nextPosX = block.GetPosition().x - block.GetSize();

					col = static_cast<int>((nextPosX - boundary.left) / block.GetSize());
					row = static_cast<int>((block.GetPosition().y - boundary.top) / block.GetSize());

					if (nextPosX < boundary.left || m_grid.HasBlock(col, row))
					{
						std::cout << "Collision Left" << std::endl;
						m_direction = Direction::None;
					}
					break;

				case Direction::Right:
					nextPosX = block.GetPosition().x + block.GetSize();

					col = static_cast<int>((nextPosX - boundary.left) / block.GetSize());
					row = static_cast<int>((block.GetPosition().y - boundary.top) / block.GetSize());

					if (nextPosX >= boundary.left + boundary.width || m_grid.HasBlock(col, row))
					{
						std::cout << "Collision Right" << std::endl;
						m_direction = Direction::None;
					}
					break;

				case Direction::Up:
					nextPosY = block.GetPosition().y - block.GetSize();

					col = static_cast<int>((block.GetPosition().x - boundary.left) / block.GetSize());
					row = static_cast<int>((nextPosY - boundary.top) / block.GetSize());

					if (nextPosY < boundary.top || m_grid.HasBlock(col, row))
					{
						std::cout << "Collision Up" << std::endl;
						m_direction = Direction::None;
					}
					break;

				case Direction::Down:
					nextPosY = block.GetPosition().y + block.GetSize();

					col = static_cast<int>((block.GetPosition().x - boundary.left) / block.GetSize());
					row = static_cast<int>((nextPosY - boundary.top) / block.GetSize());

					if (nextPosY >= boundary.top + boundary.height || m_grid.HasBlock(col, row))
					{
						std::cout << "Collision Down" << std::endl;
						m_direction = Direction::None;
						m_hasLanded = true;
					}
					break;
			}
		}

		for (auto& block : m_blocks)
		{
			block.SetDirection(m_direction);
		}
	}
}

void Shape::Update(float dt)
{
	for (auto& block : m_blocks)
	{
		block.Update(dt);

		if (m_hasLanded)
		{
			m_grid.AddBlock(block);
		}
	}

	SetDirection(Direction::None);
}

void Shape::Draw(sf::RenderWindow& window)
{
	for (auto& block : m_blocks)
	{
		block.Draw(window);
	}
}

std::vector<Block>& Shape::GetBlocks()
{
	return m_blocks;
}

bool Shape::HasLanded() const
{
	return m_hasLanded;
}
