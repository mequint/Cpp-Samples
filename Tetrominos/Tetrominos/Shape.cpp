#include "Shape.h"

#include <iostream> // For debug purposes, remove later

Shape::Shape(ShapeType type, Grid& grid) : m_hasLanded(false), m_grid(grid)
{
	const float blockSize = 16.0f;
	const std::unordered_map<ShapeType, sf::Color> TetrominoColors
	{
		{ ShapeType::I, sf::Color::Cyan },
		{ ShapeType::J, sf::Color::Blue },
		{ ShapeType::L, sf::Color(255, 165, 0, 1)},		// Orange
		{ ShapeType::O, sf::Color::Yellow },
		{ ShapeType::S, sf::Color::Green },
		{ ShapeType::T, sf::Color(128, 0, 128, 1)},		// Purple
		{ ShapeType::Z, sf::Color::Red }
	};

	sf::Color color = TetrominoColors.find(type)->second;		// Should perform a check...but this should also be in a factory

	for (int i = 0; i < 4; ++i)
	{
		m_blocks.emplace_back(blockSize);
	}
	
	switch (type)
	{
		case ShapeType::I:
			std::cout << "I Block" << std::endl;

			m_position = sf::Vector2f(0.0f, 0.0f);
			m_origin = sf::Vector2f(2.0f * blockSize, 2.0f * blockSize);

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
			std::cout << "J Block" << std::endl;

			m_position = sf::Vector2f(0.0f, 0.0f);
			m_origin = sf::Vector2f(1.5f * blockSize, 1.5f * blockSize);

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
			std::cout << "L Block" << std::endl;

			m_position = sf::Vector2f(0.0f, 0.0f);
			m_origin = sf::Vector2f(1.5f * blockSize, 1.5f * blockSize);

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
			std::cout << "O Block" << std::endl;

			m_position = sf::Vector2f(0.0f, 0.0f);
			m_origin = sf::Vector2f(blockSize, blockSize);

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
			std::cout << "S Block" << std::endl;

			m_position = sf::Vector2f(0.0f, 0.0f);
			m_origin = sf::Vector2f(1.5f * blockSize, 1.5f * blockSize);

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
			std::cout << "T Block" << std::endl;

			m_position = sf::Vector2f(0.0f, 0.0f);
			m_origin = sf::Vector2f(1.5f * blockSize, 1.5f * blockSize);

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
			std::cout << "Z Block" << std::endl;

			m_position = sf::Vector2f(0.0f, 0.0f);
			m_origin = sf::Vector2f(1.5f * blockSize, 1.5f * blockSize);

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

void Shape::SetRotation(Rotation rotation)
{
	m_rotation = rotation;
}

void Shape::Update(float dt)
{
	if (m_direction != Direction::None)
	{
		float blockSize = m_blocks[0].GetSize();

		switch (m_direction)
		{
			case Direction::Left:
				m_position.x -= blockSize;
				break;

			case Direction::Right:
				m_position.x += blockSize;
				break;

			case Direction::Up:
				m_position.y -= blockSize;
				break;

			case Direction::Down:
				m_position.y += blockSize;
				break;
		}

		for (auto& block : m_blocks)
		{
			block.Update(dt);
			if (m_hasLanded)
			{
				m_grid.AddBlock(block);
			}
		}
	}

	for (auto& block : m_blocks)
	{
		if (m_rotation != Rotation::None)
		{
			// Screen to Local Space
			float localX = m_position.x - block.GetPosition().x + m_origin.x;
			float localY = m_position.y - block.GetPosition().y + m_origin.y;

			float x1 = -localY;
			float y1 = localX;

			float newX = -localY + m_position.x + m_origin.x;
			float newY = localX + m_position.y + m_origin.y;
			block.SetPosition(newX, newY);
			
			/*
			block.SetPosition(block.GetPosition().x + m_position.x + m_origin.x,
				block.GetPosition().y + m_position.y + m_origin.y);
			*/

			/*
			std::cout <<
				"(" << block.GetPosition().x << "," << block.GetPosition().y << ") -> " <<
				"(" << localX << "," << localY << ")" << std::endl;
			*/
		}
	}

	if (m_rotation != Rotation::None)
		std::cout << std::endl;

	SetRotation(Rotation::None);
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
