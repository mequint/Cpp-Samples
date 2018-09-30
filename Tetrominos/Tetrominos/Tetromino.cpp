#include "Tetromino.h"

Tetromino::Tetromino(TetrominoType type)
{
	const float blockSize = 16.0f;
	const std::unordered_map<TetrominoType, sf::Color> TetrominoColors
	{
		{ TetrominoType::I, sf::Color::Red },
		{ TetrominoType::J, sf::Color::Blue },
		{ TetrominoType::L, sf::Color::Green },
		{ TetrominoType::O, sf::Color::White },
		{ TetrominoType::S, sf::Color::Cyan },
		{ TetrominoType::T, sf::Color::Magenta },
		{ TetrominoType::Z, sf::Color::Yellow }
	};

	m_color = TetrominoColors.find(type)->second;		// Should perform a check...but this should also be in a factory

	for (int i = 0; i < 4; ++i)
	{
		m_blocks.emplace_back(blockSize);
	}
	
	switch (type)
	{
		case TetrominoType::I:
			m_position = sf::Vector2f(0.0f, 0.0f);
			
			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(m_color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(m_color);
			m_blocks[2].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[2].SetColor(m_color);
			m_blocks[3].SetPosition(0.0f, blockSize * 3.0f);
			m_blocks[3].SetColor(m_color);
		break;

		case TetrominoType::J:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(blockSize, 0.0f);
			m_blocks[0].SetColor(m_color);
			m_blocks[1].SetPosition(blockSize, blockSize);
			m_blocks[1].SetColor(m_color);
			m_blocks[2].SetPosition(blockSize, blockSize * 2.0f);
			m_blocks[2].SetColor(m_color);
			m_blocks[3].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[3].SetColor(m_color);
		break;

		case TetrominoType::L:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(m_color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(m_color);
			m_blocks[2].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[2].SetColor(m_color);
			m_blocks[3].SetPosition(blockSize, blockSize * 2.0f);
			m_blocks[3].SetColor(m_color);
		break;

		case TetrominoType::O:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(m_color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(m_color);
			m_blocks[2].SetPosition(blockSize, 0.0f);
			m_blocks[2].SetColor(m_color);
			m_blocks[3].SetPosition(blockSize, blockSize);
			m_blocks[3].SetColor(m_color);
		break;

		case TetrominoType::S:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(m_color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(m_color);
			m_blocks[2].SetPosition(blockSize, blockSize);
			m_blocks[2].SetColor(m_color);
			m_blocks[3].SetPosition(blockSize, blockSize * 2.0f);
			m_blocks[3].SetColor(m_color);
		break;

		case TetrominoType::T:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(0.0f, 0.0f);
			m_blocks[0].SetColor(m_color);
			m_blocks[1].SetPosition(blockSize, 0.0f);
			m_blocks[1].SetColor(m_color);
			m_blocks[2].SetPosition(blockSize * 2.0f, 0.0f);
			m_blocks[2].SetColor(m_color);
			m_blocks[3].SetPosition(blockSize, blockSize);
			m_blocks[3].SetColor(m_color);
		break;

		case TetrominoType::Z:
			m_position = sf::Vector2f(0.0f, 0.0f);

			m_blocks[0].SetPosition(blockSize, 0.0f);
			m_blocks[0].SetColor(m_color);
			m_blocks[1].SetPosition(0.0f, blockSize);
			m_blocks[1].SetColor(m_color);
			m_blocks[2].SetPosition(blockSize, blockSize);
			m_blocks[2].SetColor(m_color);
			m_blocks[3].SetPosition(0.0f, blockSize * 2.0f);
			m_blocks[3].SetColor(m_color);
		break;
	}
}

void Tetromino::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Tetromino::Move(Direction direction)
{
	const float blockSize = 16.0f;
	switch (direction)
	{
		case Direction::Up:
			m_position += sf::Vector2f(0.0f, -blockSize);
			break;
		case Direction::Down:
			m_position += sf::Vector2f(0.0f, blockSize);
			break;
		case Direction::Left:
			m_position += sf::Vector2f(-blockSize, 0.0f);
			break;
		case Direction::Right:
			m_position += sf::Vector2f(blockSize, 0.0f);
			break;
	}
}

void Tetromino::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_blocks.size(); ++i)
	{
		auto localPos = m_blocks[i].GetPosition();
		m_blocks[i].SetPosition(m_position.x + localPos.x, m_position.y + localPos.y);

		m_blocks[i].Draw(window);
		m_blocks[i].SetPosition(localPos.x, localPos.y);
	}
}
