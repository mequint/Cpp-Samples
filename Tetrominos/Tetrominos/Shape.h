#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Grid.h"
#include "Movement.h"
#include "ShapeType.h"

using Blocks = std::vector<sf::Vector2i>;

class Shape
{
	public:
		Shape();
		Shape(ShapeType type, sf::Vector2f m_referencePoint);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		void SetCellPosition(int x, int y);
		void SetMovement(Movement movement);
		void SetLanded(bool landed);

		bool HasLanded() const;
		Blocks GetBlocks();
		Blocks GetNextRotation(Movement rotation);
		sf::Vector2i GetCellPosition();
		Movement GetMovement();
		ShapeType GetType();

	private:
		sf::Vector2i m_cellPosition;
		float m_blockSize;

		std::vector<Blocks> m_blocks;
		int m_rotationIndex;

		ShapeType m_type;

		sf::Vector2f m_referencePoint;

		Movement m_movement;

		bool m_hasLanded;
};