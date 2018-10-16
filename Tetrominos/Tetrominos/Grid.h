#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "ShapeType.h"

class Grid
{
	public:
		Grid();
		Grid(int columns, int rows, int posX, int posY, int cellSize);

		void Draw(sf::RenderWindow& renderWindow);

		void ToggleVisibility();

		sf::FloatRect GetGridZone();
		int GetCellSize() const;

		void AddBlock(int col, int row, int type);
		bool HasBlock(int col, int row);

		sf::Color GetBlockColor(ShapeType type);

		int RemoveCompleteLines();

	private:

		sf::Vector2i m_position;
		int m_cellSize;

		std::vector<std::vector<int>> m_blockPile;
		int m_columns, m_rows;

		bool m_visible;
};