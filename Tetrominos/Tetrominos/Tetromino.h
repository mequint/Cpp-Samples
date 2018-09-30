#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Block.h"
#include "Direction.h"

enum class TetrominoType { I, J, L, O, S, T, Z };

class Tetromino
{
	public:
		Tetromino(TetrominoType type);

		void SetPosition(float x, float y);

		void Move(Direction direction);

		void Draw(sf::RenderWindow& window);

	private:
		sf::Vector2f m_position;
		sf::Vector2f m_origin;
		sf::Color m_color;

		std::vector<Block> m_blocks;
};