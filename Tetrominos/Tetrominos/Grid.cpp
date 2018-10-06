#include "Grid.h"

Grid::Grid(int columns, int rows, int posX, int posY, int cellSize) :
	m_columns(columns), m_rows(rows), m_posX(posX), m_posY(posY), m_cellSize(cellSize), m_visible(false),
	m_gridZone(posX, posY, columns * cellSize, rows * cellSize), m_blockPile()
{}

void Grid::Draw(sf::RenderWindow & renderWindow)
{
	if (m_visible)
	{ 
		sf::RectangleShape cell(sf::Vector2f((float)m_cellSize, (float)m_cellSize));
		cell.setFillColor(sf::Color::Transparent);
		cell.setOutlineColor(sf::Color::White);
		cell.setOutlineThickness(-1.0f);

		for (int i = 0; i < m_columns; ++i)
		{
			for (int j = 0; j < m_rows; ++j)
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

sf::FloatRect Grid::GetGridZone()
{
	return m_gridZone;
}
