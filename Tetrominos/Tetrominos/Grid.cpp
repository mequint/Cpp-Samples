#include "Grid.h"

#include <unordered_map>


Grid::Grid(int columns, int rows, int posX, int posY, int cellSize) :
	m_visible(true), m_columns(columns), m_rows(rows), m_position(posX, posY), m_cellSize(cellSize), m_blockPile(columns, std::vector<int>(rows, 0))
{
}

void Grid::Draw(sf::RenderWindow& renderWindow)
{
	sf::RectangleShape cell(sf::Vector2f((float)m_cellSize, (float)m_cellSize));

	for (auto col = 0; col < m_blockPile.size(); ++col)
	{
		for (auto row = 0; row < m_blockPile[col].size(); ++row)
		{
			if (m_blockPile[col][row])
			{
				sf::Color color = GetBlockColor((ShapeType)(m_blockPile[col][row]));
				cell.setFillColor(color);

				sf::Color outlineColor = color;
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
			cell.setPosition(static_cast<float>(m_position.x + col * m_cellSize), static_cast<float>(m_position.y + row * m_cellSize));
			renderWindow.draw(cell);
		}
	}
}

void Grid::ToggleVisibility()
{
	m_visible = !m_visible;
}

sf::FloatRect Grid::GetGridZone()
{
	return sf::FloatRect(sf::Vector2f(m_position.x, m_position.y), sf::Vector2f(m_columns * m_cellSize, m_rows * m_cellSize));
}

int Grid::GetCellSize() const
{
	return m_cellSize;
}

void Grid::AddBlock(int col, int row, int type)
{
	m_blockPile[col][row] = type;
}

bool Grid::HasBlock(int col, int row)
{
	return m_blockPile[col][row];
}

sf::Color Grid::GetBlockColor(ShapeType type)
{
	switch (type)
	{
		case ShapeType::I: return sf::Color::Cyan;
		case ShapeType::J: return sf::Color::Blue;
		case ShapeType::L: return sf::Color(255, 165, 0);
		case ShapeType::O: return sf::Color::Yellow;
		case ShapeType::S: return sf::Color::Green;
		case ShapeType::T: return sf::Color(128, 0, 128);
		case ShapeType::Z: return sf::Color::Red;
	}

	return sf::Color::Magenta;
}