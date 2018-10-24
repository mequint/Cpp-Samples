#include "Shape.h"

#include "BlockHelper.h"

Shape::Shape() {}

Shape::Shape(ShapeType type, float blockSize) : m_type(type), m_hasLanded(false), m_rotationIndex(0), m_blockSize(blockSize), m_isShadow(false)
{	
	switch (type)
	{
		case ShapeType::I:
		{
			Blocks block1;
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			block1.emplace_back(sf::Vector2i(3, 1));
			m_blocks.emplace_back(block1);

			Blocks block2;
			block2.emplace_back(sf::Vector2i(2, 0));
			block2.emplace_back(sf::Vector2i(2, 1));
			block2.emplace_back(sf::Vector2i(2, 2));
			block2.emplace_back(sf::Vector2i(2, 3));
			m_blocks.emplace_back(block2);

			Blocks block3;
			block3.emplace_back(sf::Vector2i(0, 2));
			block3.emplace_back(sf::Vector2i(1, 2));
			block3.emplace_back(sf::Vector2i(2, 2));
			block3.emplace_back(sf::Vector2i(3, 2));
			m_blocks.emplace_back(block3);

			Blocks block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			block4.emplace_back(sf::Vector2i(1, 3));
			m_blocks.emplace_back(block4);

			m_spawnPoint = sf::Vector2i(3, 1);
			break;
		}

		case ShapeType::J:
		{
			Blocks block1;
			block1.emplace_back(sf::Vector2i(0, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block1);

			Blocks block2;
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(2, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block2);

			Blocks block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			block3.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block3);

			Blocks block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			block4.emplace_back(sf::Vector2i(0, 2));
			m_blocks.emplace_back(block4);

			m_spawnPoint = sf::Vector2i(4, 1);
			break;
		}

		case ShapeType::L:
		{
			Blocks block1;
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			block1.emplace_back(sf::Vector2i(2, 0));
			m_blocks.emplace_back(block1);

			Blocks block2;
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			block2.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block2);

			Blocks block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(0, 2));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block3);

			Blocks block4;
			block4.emplace_back(sf::Vector2i(0, 0));
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block4);

			m_spawnPoint = sf::Vector2i(4, 1);

			break;
		}

		case ShapeType::O:
		{
			Blocks block1;
			block1.emplace_back(sf::Vector2i(0, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block1);

			Blocks block2;
			block2.emplace_back(sf::Vector2i(0, 0));
			block2.emplace_back(sf::Vector2i(0, 1));
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block2);

			Blocks block3;
			block3.emplace_back(sf::Vector2i(0, 0));
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 0));
			block3.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block3);

			Blocks block4;
			block4.emplace_back(sf::Vector2i(0, 0));
			block4.emplace_back(sf::Vector2i(0, 1));
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block4);

			m_spawnPoint = sf::Vector2i(4, 1);

			break;
		}

		case ShapeType::S:
		{
			Blocks block1;
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(2, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			m_blocks.emplace_back(block1);

			Blocks block2;
			block2.emplace_back(sf::Vector2i(0, 0));
			block2.emplace_back(sf::Vector2i(0, 1));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block2);

			Blocks block3;
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			block3.emplace_back(sf::Vector2i(0, 2));
			block3.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block3);

			Blocks block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(2, 1));
			block4.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block4);

			m_spawnPoint = sf::Vector2i(4, 2);

			break;
		}

		case ShapeType::T:
		{
			Blocks block1;
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(0, 1));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block1);

			Blocks block2;
			block2.emplace_back(sf::Vector2i(1, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			block2.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block2);

			Blocks block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(2, 1));
			block3.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block3);

			Blocks block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(0, 1));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block4);

			m_spawnPoint = sf::Vector2i(4, 1);

			break;
		}

		case ShapeType::Z:
		{
			Blocks block1;
			block1.emplace_back(sf::Vector2i(0, 0));
			block1.emplace_back(sf::Vector2i(1, 0));
			block1.emplace_back(sf::Vector2i(1, 1));
			block1.emplace_back(sf::Vector2i(2, 1));
			m_blocks.emplace_back(block1);

			Blocks block2;
			block2.emplace_back(sf::Vector2i(2, 0));
			block2.emplace_back(sf::Vector2i(1, 1));
			block2.emplace_back(sf::Vector2i(2, 1));
			block2.emplace_back(sf::Vector2i(1, 2));
			m_blocks.emplace_back(block2);

			Blocks block3;
			block3.emplace_back(sf::Vector2i(0, 1));
			block3.emplace_back(sf::Vector2i(1, 1));
			block3.emplace_back(sf::Vector2i(1, 2));
			block3.emplace_back(sf::Vector2i(2, 2));
			m_blocks.emplace_back(block3);

			Blocks block4;
			block4.emplace_back(sf::Vector2i(1, 0));
			block4.emplace_back(sf::Vector2i(0, 1));
			block4.emplace_back(sf::Vector2i(1, 1));
			block4.emplace_back(sf::Vector2i(0, 2));
			m_blocks.emplace_back(block4);

			m_spawnPoint = sf::Vector2i(4, 1);

			break;
		}
	}
}

Shape::Shape(const Shape & shape)
{
	m_cellPosition = shape.m_cellPosition;
	m_blockSize = shape.m_blockSize;

	m_blocks = shape.m_blocks;
	m_rotationIndex = shape.m_rotationIndex;

	m_spawnPoint = shape.m_spawnPoint;
	m_type = shape.m_type;
	m_isShadow = shape.m_isShadow;
	m_onField = shape.m_onField;

	m_referencePoint = shape.m_referencePoint;

	m_movement = shape.m_movement;

	m_hasLanded = shape.m_hasLanded;
}

void Shape::Update(float dt)
{
	if (m_movement != Movement::None)
	{
		switch (m_movement)
		{
			case Movement::Left:
				m_cellPosition.x -= 1;
				break;

			case Movement::Right:
				m_cellPosition.x += 1;
				break;

			case Movement::Up:
				m_cellPosition.y -= 1;
				break;

			case Movement::Down:
				m_cellPosition.y += 1;
				break;

			case Movement::CW:
				if (m_rotationIndex == 3)
				{
					m_rotationIndex = 0;
				}
				else
				{
					m_rotationIndex++;
				}
				break;

			case Movement::CCW:
				if (m_rotationIndex == 0)
				{
					m_rotationIndex = 3;
				}
				else
				{
					m_rotationIndex--;
				}
				break;
		}

		m_movement = Movement::None;
	}
}

void Shape::Draw(sf::RenderWindow& window)
{
	if (m_blocks.empty()) return;

 	for (auto block : m_blocks[m_rotationIndex])
	{
		int blockY = m_cellPosition.y + block.y;

		auto cell = (blockY == 1 && m_onField) ?
			sf::RectangleShape(sf::Vector2f(m_blockSize, m_blockSize / 4.0f)) :
			sf::RectangleShape(sf::Vector2f(m_blockSize, m_blockSize));

		auto offset = (blockY == 1 && m_onField) ? m_blockSize - m_blockSize / 4.0f : 0;

		sf::Color color = BlockHelper::GetBlockColor(m_type);
		
		if (m_isShadow)
		{
			color.a = 128;
		}
		cell.setFillColor(color);

		sf::Color outlineColor = color;
		outlineColor.r = 2 * outlineColor.r / 5;
		outlineColor.g = 2 * outlineColor.g / 5;
		outlineColor.b = 2 * outlineColor.b / 5;

		if (m_isShadow)
		{
			color.a = 128;
		}

		cell.setOutlineColor(outlineColor);

		cell.setOutlineThickness(-1.0f);
		cell.setPosition(
			m_referencePoint.x + (m_cellPosition.x + block.x) * m_blockSize,
			m_referencePoint.y + (m_cellPosition.y + block.y) * m_blockSize + offset);

		window.draw(cell);
	}
}

// ***** Accessors / Mutators ***** //

void Shape::SetReferencePoint(sf::Vector2f referencePoint)
{
	m_referencePoint = referencePoint;
}

void Shape::SetCellPosition(int x, int y)
{
	m_cellPosition = sf::Vector2i(x, y);
}

void Shape::SetMovement(Movement movement)
{
	m_movement = movement;
}

void Shape::SetLanded(bool landed)
{
	m_hasLanded = landed;
}

void Shape::SetOnField(bool onField)
{
	m_onField = onField;
}

void Shape::SetRotationIndex(int index)
{
	m_rotationIndex = 0;
}

void Shape::SetShadow(bool shadow)
{
	m_isShadow = shadow;
}

bool Shape::HasLanded() const
{
	return m_hasLanded;
}

Blocks Shape::GetBlocks()
{
	return m_blocks[m_rotationIndex];
}

Blocks Shape::GetNextRotation(Movement rotation)
{
	int index = m_rotationIndex;
	if (rotation == Movement::CW)
	{
		index--;
		if (index < 0) index = 3;
	}
	else if (rotation == Movement::CCW)
	{
		index++;
		if (index > 3) index = 0;
	}

	return m_blocks[index];
}

sf::Vector2i Shape::GetCellPosition()
{
	return m_cellPosition;
}

Movement Shape::GetMovement()
{
	return m_movement;
}

ShapeType Shape::GetType()
{
	return m_type;
}

sf::Vector2i Shape::GetSpawnPoint()
{
	return m_spawnPoint;
}

float Shape::GetBlockSize()
{
	return m_blockSize;
}