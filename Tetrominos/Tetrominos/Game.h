#pragma once

#include "Context.h"
#include "StateManager.h"
#include "Window.h"

#include "RandomGenerator.h"

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
		Context m_context;
		StateManager m_stateManager;
		Window m_window;
};