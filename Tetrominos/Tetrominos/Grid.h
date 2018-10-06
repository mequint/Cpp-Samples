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

		std::vector<std::vector<Block>> m_blockPile;

	private:
		int m_posX, m_posY;
		int m_columns, m_rows;
		int m_cellSize;

		bool m_visible;

		sf::FloatRect m_gridZone;
};