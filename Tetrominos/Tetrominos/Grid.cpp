#include "Grid.h"

Grid::Grid(int columns, int rows, int posX, int posY, int cellSize) :
	m_columns(columns), m_rows(rows), m_posX(posX), m_posY(posY), m_cellSize(cellSize), m_visible(false),
	m_gridZone(posX, posY, columns * cellSize, rows * cellSize), m_blockPile(columns, std::vector<int>(rows, 0))
{

}

void Grid::Draw(sf::RenderWindow & renderWindow)
{
	if (m_visible)
	{ 
		sf::RectangleShape cell(sf::Vector2f((float)m_cellSize, (float)m_cellSize));

		for (int col = 0; col < m_blockPile.size(); ++col)
		{
			for (int row = 0; row < m_blockPile[col].size(); ++row)
			{
				if (m_blockPile[col][row])
				{
					cell.setFillColor(sf::Color::Red);

					auto outlineColor = sf::Color::Red;
					outlineColor.r = 3 * outlineColor.r / 5;
					outlineColor.g = 3 * outlineColor.g / 5;
					outlineColor.b = 3 * outlineColor.b / 5;
					cell.setOutlineColor(outlineColor);
				}
				else
				{
					cell.setFillColor(sf::Color::Transparent);
					cell.setOutlineColor(sf::Color::White);
				}

				cell.setOutlineThickness(-1.0f);
				cell.setPosition((float)(m_posX + col * m_cellSize), (float)(m_posY + row * m_cellSize));
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

void Grid::AddBlock(Block & block)
{
	int column = (block.GetPosition().x - m_posX) / m_cellSize;
	int row = (block.GetPosition().y - m_posY) / m_cellSize;

	m_blockPile[column][row] = 1;
}

bool Grid::HasBlock(int col, int row)
{
	return m_blockPile[col][row];
}
