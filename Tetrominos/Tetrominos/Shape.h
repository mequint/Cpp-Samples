#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Movement.h"
#include "ShapeType.h"

using Blocks = std::vector<sf::Vector2i>;

class Shape
{
	public:
		Shape();
		Shape(ShapeType type, float blockSize);
		Shape(const Shape& shape);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

		void SetReferencePoint(sf::Vector2f referencePoint);
		void SetCellPosition(int x, int y);
		void SetMovement(Movement movement);
		void SetLanded(bool landed);
		void SetOnField(bool onField);
		void SetRotationIndex(int index);
		void SetShadow(bool shadow);

		bool HasLanded() const;
		Blocks GetBlocks();
		Blocks GetNextRotation(Movement rotation);
		sf::Vector2i GetCellPosition();
		Movement GetMovement();
		ShapeType GetType();
		sf::Vector2i GetSpawnPoint();
		float GetBlockSize();

	private:
		sf::Vector2i m_cellPosition;
		float m_blockSize;

		std::vector<Blocks> m_blocks;
		int m_rotationIndex;

		sf::Vector2i m_spawnPoint;
		ShapeType m_type;
		bool m_isShadow;
		bool m_onField;

		sf::Vector2f m_referencePoint;

		Movement m_movement;

		bool m_hasLanded;
};