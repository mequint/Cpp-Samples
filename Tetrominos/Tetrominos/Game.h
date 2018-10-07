#pragma once

#include "BaseState.h"
#include "Random.h"
#include "Window.h"

class Game
{
	public:
		Game();
		~Game();

		void Update();
		void Draw();
		void PostProcess();

		sf::Time GetElapsedtime();

		Window* GetWindow();

	private:
		void RestartClock();

		sf::Clock m_clock;
		sf::Time m_elapsedTime;

		// Contextual items
		Random m_rng;
		Window m_window;

		// Add to state machine
		BaseState* m_currentState;
};