#pragma once

#include "Context.h"
#include "StateManager.h"
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

		void SetupBindings();

		sf::Clock m_clock;
		sf::Time m_elapsedTime;

		// Contextual items
		Context m_context;
		Window m_window;
		StateManager m_stateManager;
};

// A buggy dependency...the Window must be declared above the State Manager (it will cause a break in the states when they are Destroyed).