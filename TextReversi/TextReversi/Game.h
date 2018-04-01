#pragma once

#include "GameContext.h"
#include "StateManager.h"

class Game
{
	public:
		Game();

		GameContext GetContext();

		void Run();
		bool IsRunning() const;

	private:

		GameContext m_context;
		StateManager m_stateManager;
};