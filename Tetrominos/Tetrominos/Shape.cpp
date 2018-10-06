#include "Shape.h"

Shape::Shape(ShapeType type)
{
	m_collides = false;

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
	for (auto& block : m_blocks)
	{
		block.SetDirection(direction);
	}
}

void Shape::Update(float dt)
{
	for (auto& block : m_blocks)
	{
		block.Update(dt);
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

void Shape::Collides(std::vector<Block>& blocks, const sf::FloatRect& gridZone)
{
	float blockSize = m_blocks[0].GetSize();

	sf::Vector2f dirVec;;
	switch (m_direction)
	{
		case Direction::Left:
			dirVec = sf::Vector2f(-blockSize, 0.0f);
			break;

		case Direction::Right:
			dirVec = sf::Vector2f(blockSize, 0.0f);
			break;

		case Direction::Up:
			dirVec = sf::Vector2f(0.0f, -blockSize);
			break;

		case Direction::Down:
			dirVec = sf::Vector2f(0.0f, blockSize);
			break;

		default:
			dirVec = sf::Vector2f(0.0f, 0.0f);
	}

	for (auto& block : m_blocks)
	{
		sf::Vector2f newPosition = block.GetPosition() + dirVec;
		if (newPosition.x < gridZone.left || newPosition.x >= gridZone.left + gridZone.width ||
			newPosition.y < gridZone.top || newPosition.y >= gridZone.top + gridZone.height)
		{
			m_collides = true;
			return;
		}

		for (auto& other : blocks)
		{
			if (block.GetAABB().intersects(other.GetAABB()))
			{
				m_collides = true;
				return;
			}
		}
	}

	m_collides = false;
}

bool Shape::GetCollides() const
{
	return m_collides;
}
