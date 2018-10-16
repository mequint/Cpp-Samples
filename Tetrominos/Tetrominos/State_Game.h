#pragma once

#include "BaseState.h"

#include "Grid.h"
#include "RandomGenerator.h"
#include "Shape.h"

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

		int m_blockSize;

		Grid m_grid;
		Shape m_lander;

		int m_spawnX, m_spawnY;

		float m_currentFallTime;
		float m_nextFallTime;

		int m_lines;
		int m_speedUp;
};