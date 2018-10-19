#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Grid.h"
#include "Direction.h"
#include "ShapeType.h"

using Block = std::vector<sf::Vector2i>;

class Shape
{
	public:
		Shape();
		Shape(ShapeType type, Grid& grid);

		void SetCellPosition(int x, int y);
		void SetDirection(Direction direction);
		void SetRotation(Rotation rotation);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		bool HasLanded() const;

		std::vector<sf::Vector2i> GetBlocks();
		sf::Vector2i GetPosition();
		ShapeType GetType();

	private:
		sf::Vector2i m_cellPosition;

		std::vector<Block> m_blocks;
		int m_rotationIndex;

		ShapeType m_type;

		Grid m_grid;

		Direction m_direction;
		Rotation m_rotation;

		bool m_hasLanded;
};