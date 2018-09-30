#pragma once

#include <SFML/Graphics.hpp>

class Grid
{
	public:
		Grid(int width, int height, int posX, int posY, int cellSize);

		void Draw(sf::RenderWindow& renderWindow);

		void ToggleVisibility();

	private:
		int m_posX, m_posY;
		int m_width, m_height;
		int m_cellSize;

		bool m_visible;
};