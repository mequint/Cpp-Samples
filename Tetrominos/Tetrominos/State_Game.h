#pragma once

#include "BaseState.h"

#include "Grid.h"
#include "RandomGenerator.h"
#include "Shape.h"
#include "ShapeBox.h"
#include "TextBox.h"

class State_Game : public BaseState
{
	public:
		State_Game(StateManager* stateManager);
		~State_Game();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void HandleEvents();
		void Update(const sf::Time& time);
		void Draw();

	private:
		RandomGenerator m_randomGenerator;

		// Resources
		sf::Font m_font;

		// User Interface
		ShapeBox m_holdBox;
		ShapeBox m_nextBox;
		TextBox m_linesBox;

		// Game variables
		int m_blockSize;

		Grid m_grid;
		Shape m_lander;
		Shape m_next;

		int m_spawnX, m_spawnY;

		float m_currentFallTime;
		float m_nextFallTime;

		int m_lines;
		int m_speedUp;
};