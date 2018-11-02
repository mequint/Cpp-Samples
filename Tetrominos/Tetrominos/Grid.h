#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Shape.h"
#include "Tweener.h"

enum class GridState { Waiting, Animating, RemovingLines };

class Grid
{
	public:
		Grid(int columns, int rows, int posX, int posY, int cellSize);

		void CheckCollisions(Shape& shape);
		void Update(Shape& shape, float dt);
		void Draw(sf::RenderWindow& renderWindow);

		void SlamShape(Shape & shape);
		Shape CastShadow(Shape& shape);

		bool HasBlock(int col, int row);
		sf::Vector2f GetPosition();
		int GetLinesRemoved() const;

	private:
		void DrawBlock(sf::RenderWindow& renderWindow, int col, int row);
		void DrawGridCell(int row, int col, sf::RenderWindow & renderWindow);

		sf::Vector2f m_position;
		int m_cellSize;

		std::vector<std::vector<int>> m_blockPile;
		int m_columns, m_rows;

		GridState m_state;
		std::vector<int> m_linesToRemove;

		// Animation
		IntTweener m_alphaTweener;
};