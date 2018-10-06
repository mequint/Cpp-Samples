#pragma once

#include <SFML/Graphics.hpp>

#include "Direction.h"

class Block
{
	public:
		Block(float blockSize);

		void Draw(sf::RenderWindow& window);
		void Update(float dt);

		void SetPosition(sf::Vector2f position);
		void SetPosition(float x, float y);
		void SetColor(sf::Color color);
		void SetDirection(Direction direction);

		sf::Vector2f GetPosition();
		float GetSize() const;
		sf::FloatRect GetAABB();

	private:
		void UpdateRectShape();
		void UpdateAABB();

		// Stats
		sf::Vector2f m_position;
		float m_blockSize;

		// Drawing
		sf::Color m_color;
		sf::RectangleShape m_rectShape;

		// Collision
		sf::FloatRect m_AABB;
		Direction m_direction;
};