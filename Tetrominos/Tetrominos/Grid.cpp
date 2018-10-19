#include "Grid.h"

#include <unordered_map>

#include "Shape.h"

Grid::Grid() {}

Grid::Grid(int columns, int rows, int posX, int posY, int cellSize) :
	m_visible(true), m_columns(columns), m_rows(rows), m_position(posX, posY), m_cellSize(cellSize), m_blockPile(columns, std::vector<int>(rows, 0))
{
}

void Grid::CheckCollisions(Shape& shape)
{
	auto cellPos = shape.GetCellPosition();
	auto movement = shape.GetMovement();

	if (movement != Movement::None)
	{
		for (auto block : shape.GetBlocks())
		{
			int x = cellPos.x + block.x;
			int y = cellPos.y + block.y;

			switch (movement)
			{
				case Movement::Left:
				{
					x--;

					if (x < 0 || HasBlock(x, y))
					{
						shape.SetMovement(Movement::None);
						return;
					}
					break;
				}

				case Movement::Right:
				{
					x++;

					if (x >= m_columns || HasBlock(x, y))
					{
						shape.SetMovement(Movement::None);
						return;
					}
					break;
				}

				// TODO: Remove...will not need
				case Movement::Up:
				{
					y--;
					if (y < 0 || HasBlock(x, y))
					{
						shape.SetMovement(Movement::None);
						return;
					}
					break;
				}

				case Movement::Down:
				{
					y++;
					if (y >= m_rows || HasBlock(x, y))
					{
						shape.SetMovement(Movement::None);
						shape.SetLanded(true);
						return;
					}
					break;
				}

				case Movement::CW:
				case Movement::CCW:
				{
					Blocks blocks = shape.GetNextRotation(movement);

					for (auto block : blocks)
					{
						int x = cellPos.x + block.x;
						int y = cellPos.y + block.y;

						bool outOfBounds = (x < 0 || x >= m_columns) || (y < 0 || y >= m_rows * m_cellSize);

						if (outOfBounds || HasBlock(block.x, block.y))
						{
							shape.SetMovement(Movement::None);
							return;
						}
					}
					break;
				}
			}
		}
	}
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

				sf::Color outlineColor = sf::Color::White;
				outlineColor.a = 3 * outlineColor.a / 5;
				cell.setOutlineColor(outlineColor);
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

sf::Vector2f Grid::GetPosition()
{
	return m_position;
}

int Grid::RemoveCompleteLines()
{
	int score = 0;
	// We want to check every row...not column
	int rows = m_blockPile[0].size();

	for (int i = 0; i < rows; ++i)
	{
		bool completeLine = true;

		for (int j = m_blockPile.size() - 1; j >= 0; --j)
		{
			if (!m_blockPile[j][i])
			{
				completeLine = false;
			}
		}

		if (completeLine)
		{
			for (int k = i; k > 0; --k)
			{
				for (int l = 0; l < m_blockPile.size(); ++l)
				{
					int temp = m_blockPile[l][k];
					m_blockPile[l][k] = m_blockPile[l][k - 1];
					m_blockPile[l][k - 1] = temp;
				}
			}

			for (int k = 0; k < m_blockPile.size(); ++k)
			{
				m_blockPile[k][0] = 0;
			}
			score++;
		}
	}

	return score;
}
