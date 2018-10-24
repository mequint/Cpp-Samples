#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "ShapeType.h"

class Shape;				/// Will need to add later...once the inversion is complete

class Grid
{
	public:
		Grid();
		Grid(int columns, int rows, int posX, int posY, int cellSize);

		void CheckCollisions(Shape& shape);

		void Update(Shape& shape, float dt);
		void SlamShape(Shape & shape);
		void Draw(sf::RenderWindow& renderWindow);

		void ToggleVisibility();

		sf::FloatRect GetGridZone();
		int GetCellSize() const;
		Shape GetShadow(Shape& shape);

		void AddBlock(int col, int row, int type);
		bool HasBlock(int col, int row);

		sf::Vector2f GetPosition();

		int RemoveCompleteLines();

	private:

		sf::Vector2f m_position;
		int m_cellSize;

		std::vector<std::vector<int>> m_blockPile;
		int m_columns, m_rows;

		bool m_visible;
};