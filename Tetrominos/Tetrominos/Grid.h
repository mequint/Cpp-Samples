#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Block.h"

class Grid
{
	public:
		Grid(int columns, int rows, int posX, int posY, int cellSize);

		void Draw(sf::RenderWindow& renderWindow);

		void ToggleVisibility();

		sf::FloatRect GetGridZone();

		void AddBlock(Block& block);
		bool HasBlock(int col, int row);

	private:
		int m_posX, m_posY;

		std::vector<std::vector<int>> m_blockPile;
		int m_columns, m_rows;
		int m_cellSize;

		bool m_visible;

		sf::FloatRect m_gridZone;
};