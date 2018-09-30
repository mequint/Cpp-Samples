#include "Grid.h"

Grid::Grid(int width, int height, int posX, int posY, int cellSize) :
	m_width(width), m_height(height), m_posX(posX), m_posY(posY), m_cellSize(cellSize), m_visible(false)
{}

void Grid::Draw(sf::RenderWindow & renderWindow)
{
	if (m_visible)
	{ 
		sf::RectangleShape cell(sf::Vector2f((float)m_cellSize, (float)m_cellSize));
		cell.setFillColor(sf::Color::Transparent);
		cell.setOutlineColor(sf::Color::White);
		cell.setOutlineThickness(-1.0f);

		for (int i = 0; i < m_width; ++i)
		{
			for (int j = 0; j < m_height; ++j)
			{
				cell.setPosition((float)(m_posX + i * m_cellSize), (float)(m_posY + j * m_cellSize));
				renderWindow.draw(cell);
			}
		}
	}
}

void Grid::ToggleVisibility()
{
	m_visible = !m_visible;
}