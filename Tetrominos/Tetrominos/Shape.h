#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Block.h"
#include "Direction.h"

enum class ShapeType { I, J, L, O, S, T, Z };

class Shape
{
	public:
		Shape(ShapeType type);

		void SetPosition(float x, float y);
		void SetDirection(Direction direction);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		std::vector<Block>& GetBlocks();

		void Collides(std::vector<Block>& blocks, const sf::FloatRect& gridZone);
		bool GetCollides() const;

	private:
		sf::Vector2f m_position;
		
		std::vector<Block> m_blocks;
		Direction m_direction;

		bool m_collides;
};