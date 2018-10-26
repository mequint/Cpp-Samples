#pragma once

#include "BaseState.h"

#include "EventManager.h"
#include "Grid.h"
#include "Label.h"
#include "RandomGenerator.h"
#include "Shape.h"
#include "ShapeBox.h"
#include "TitledTextBox.h"

class State_Game : public BaseState
{
	public:
		State_Game(StateManager* stateManager);
		~State_Game();

		void Create();
		void Destroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& time);
		void Draw();

		void Pause(EventDetails* details);
		void MoveLander(EventDetails* details);

	private:

		void SwapLanderWithHold();

		RandomGenerator m_randomGenerator;

		// Resources
		sf::Font m_font;

		// User Interface
		Label m_linesBox;
		ShapeBox m_holdBox;
		ShapeBox m_nextBox;
		TitledTextBox m_levelBox;
		TitledTextBox m_scoreBox;

		// Game variables
		float m_blockSize;

		Grid m_grid;
		Shape m_lander;
		Shape m_next;
		Shape m_hold;
		Shape m_shadow;

		float m_currentFallTime;
		float m_nextFallTime;

		int m_lines;
		int m_score;
		int m_speedUp;
};