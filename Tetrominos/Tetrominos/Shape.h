#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Block.h"
#include "Grid.h"
#include "Direction.h"

enum class ShapeType { I, J, L, O, S, T, Z };

class Shape
{
	public:
		Shape(ShapeType type, Grid& grid);

		void SetPosition(float x, float y);
		void SetDirection(Direction direction);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		std::vector<Block>& GetBlocks();
		bool HasLanded() const;

	private:
		sf::Vector2f m_position;
		
		Grid m_grid;

		std::vector<Block> m_blocks;
		Direction m_direction;

		bool m_hasLanded;
};