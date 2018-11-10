#include "Grid.h"

#include <unordered_map>

#include "BlockHelper.h"
#include "Shape.h"

Grid::Grid(int columns, int rows, int posX, int posY, int cellSize) :
	m_columns(columns), m_rows(rows), m_position(posX, posY), m_cellSize(cellSize), m_blockPile(columns, std::vector<int>(rows, 0)),
	m_alphaTweener(1.0, 0, 30, 1.0f / 120.0f), m_readyNextShape(false)
{
	m_state = GridState::Waiting;
}

void Grid::CheckCollisions(Shape& shape)
{
	if (shape.GetType() == ShapeType::None) return;

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

void Grid::Update(Shape& shape, float dt)
{
	if (m_state == GridState::Waiting)
	{
		m_readyNextShape = false;

		m_linesToRemove.clear();

		if (shape.HasLanded())
		{
			sf::Vector2i landerPos = shape.GetCellPosition();
			for (auto block : shape.GetBlocks())
			{
				int col = block.x + landerPos.x;
				int row = block.y + landerPos.y;
				int type = static_cast<int>(shape.GetType());

				m_blockPile[col][row] = type;
			}

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
					m_linesToRemove.push_back(i);
				}
			}

			if (!m_linesToRemove.empty())
			{
				m_alphaTweener.Play();
				m_state = GridState::Animating;
			}
			else
			{
				m_readyNextShape = true;
			}
		}
	}
	else if (m_state == GridState::Animating)
	{
		m_alphaTweener.Update(dt);

		if (m_alphaTweener.IsComplete())
		{
			m_alphaTweener.Reset();
			m_state = GridState::RemovingLines;
		}
	}
	else if (m_state == GridState::RemovingLines)
	{
		for (auto i : m_linesToRemove)
		{
			for (int j = i; j > 0; --j)
			{
				for (int k = 0; k < m_blockPile.size(); ++k)
				{
					int temp = m_blockPile[k][j];
					m_blockPile[k][j] = m_blockPile[k][j - 1];
					m_blockPile[k][j - 1] = temp;
				}
			}

			for (int j = 0; j < m_blockPile.size(); ++j)
			{
				m_blockPile[j][0] = 0;
			}
		}

		m_readyNextShape = true;
		m_state = GridState::Waiting;
	}
}

void Grid::SlamShape(Shape& shape)
{
	while (!shape.HasLanded())
	{
		shape.SetMovement(Movement::Down);
		CheckCollisions(shape);
		shape.Update(0.0f);
	}
}

void Grid::Draw(sf::RenderWindow& renderWindow)
{

	for (auto col = 0; col < m_blockPile.size(); ++col)
	{
		for (auto row = 1; row < m_blockPile[col].size(); ++row)
		{
			DrawGridCell(row, col, renderWindow);

			if (m_blockPile[col][row])
			{
				DrawBlock(renderWindow, col, row);
			}
		}
	}
}

void Grid::DrawBlock(sf::RenderWindow& renderWindow, int col, int row)
{
	sf::RectangleShape cell(sf::Vector2f((float)m_cellSize, (float)m_cellSize));

	sf::Color color = BlockHelper::GetBlockColor((ShapeType)(m_blockPile[col][row]));
	sf::Color outlineColor = color;
	outlineColor.r = 3 * outlineColor.r / 5;
	outlineColor.g = 3 * outlineColor.g / 5;
	outlineColor.b = 3 * outlineColor.b / 5;

	sf::Vector2f size = sf::Vector2f((float)m_cellSize, (float)m_cellSize);
	sf::Vector2f position = sf::Vector2f((float)(m_position.x + col * m_cellSize), (float)(m_position.y + row * m_cellSize));
	sf::Vector2f origin = sf::Vector2f(0.0f, 0.0f);

	if (m_state == GridState::Animating)
	{
		for (auto line : m_linesToRemove)
		{
			if (row == line)
			{
				color.a = (float)color.a * m_alphaTweener.CurrentStep();
				outlineColor.a = (float)outlineColor.a * m_alphaTweener.CurrentStep();
				origin = sf::Vector2f((float)m_cellSize / 2.0f, (float)m_cellSize / 2.0f);
				position = sf::Vector2f((float)m_position.x + col * m_cellSize + m_cellSize / 2.0f,
					(float)m_position.y + row * m_cellSize + m_cellSize / 2.0f);
			}
		}
	}
	else if (m_state == GridState::RemovingLines)
	{
		color = sf::Color::Transparent;
		outlineColor = sf::Color::Transparent;
	}

	cell.setOutlineColor(outlineColor);
	cell.setFillColor(color);
	cell.setOutlineThickness(-1.0f);

	if (row == 1)
	{
		cell.setSize(sf::Vector2f((float)m_cellSize, (float)m_cellSize / 4.0f));
		cell.setPosition(static_cast<float>(m_position.x + col * m_cellSize), static_cast<float>(m_position.y + row * m_cellSize + 3 * m_cellSize / 4));
	}
	else
	{
		cell.setSize(size);
		cell.setPosition(position);
		cell.setOrigin(origin);
	}

	renderWindow.draw(cell);
}

void Grid::DrawGridCell(int row, int col, sf::RenderWindow & renderWindow)
{
	sf::RectangleShape cell(sf::Vector2f((float)m_cellSize, (float)m_cellSize));
	cell.setFillColor(sf::Color::Transparent);

	sf::Color outlineColor = sf::Color::White;
	outlineColor.a = 3 * outlineColor.a / 5;
	cell.setOutlineColor(outlineColor);
	cell.setOutlineThickness(-1.0f);

	if (row == 1)
	{
		cell.setSize(sf::Vector2f((float)m_cellSize, (float)m_cellSize / 4.0f));
		cell.setPosition(static_cast<float>(m_position.x + col * m_cellSize), static_cast<float>(m_position.y + row * m_cellSize + 3 * m_cellSize / 4));
	}
	else
	{
		sf::Vector2f size = sf::Vector2f((float)m_cellSize, (float)m_cellSize);
		sf::Vector2f position = sf::Vector2f(static_cast<float>(m_position.x + col * m_cellSize), static_cast<float>(m_position.y + row * m_cellSize));

		cell.setSize(size);
		cell.setPosition(position);
	}

	renderWindow.draw(cell);
}

Shape Grid::CastShadow(Shape& shape)
{
	if (shape.GetType() == ShapeType::None) return Shape(ShapeType::None, shape.GetBlockSize());
	Shape shadow(shape);
	shadow.SetShadow(true);

	SlamShape(shadow);

	return shadow;
}

bool Grid::HasBlock(int col, int row)
{
	return m_blockPile[col][row];
}

sf::Vector2f Grid::GetPosition()
{
	return m_position;
}

int Grid::GetLinesRemoved() const
{
	if (m_state == GridState::Animating)
	{
		return m_linesToRemove.size();
	}

	return 0;
}

bool Grid::ReadyNextShape() const
{
	return m_readyNextShape;
}

void Grid::Reset()
{
	for (int i = 0; i < m_blockPile.size(); ++i)
	{
		for (int j = 0; j < m_blockPile[i].size(); ++j)
		{
			m_blockPile[i][j] = (int)ShapeType::None;
		}
	}

	m_state = GridState::Waiting;
	m_linesToRemove.clear();
	m_readyNextShape = false;

	m_alphaTweener.Reset();

}
