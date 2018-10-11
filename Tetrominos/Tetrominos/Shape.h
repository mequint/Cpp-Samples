#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Grid.h"
#include "Direction.h"
#include "ShapeType.h"

class Shape
{
	public:
		Shape(ShapeType type, Grid& grid);

		void SetPosition(int x, int y);
		void SetOrigin(float x, float y);

		void SetDirection(Direction direction);
		void SetRotation(Rotation rotation);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		bool HasLanded() const;

		std::vector<sf::Vector2i> GetBlocks();
		sf::Vector2i GetPosition();
		ShapeType GetType();


	private:
		sf::Vector2i m_position;
		sf::Vector2f m_origin;

		std::vector<sf::Vector2i> m_blocks;
		ShapeType m_type;

		Grid m_grid;

		Direction m_direction;
		Rotation m_rotation;

		bool m_hasLanded;
};