#pragma once

#include "GameState.h"

class ExitingGameState : public GameState
{
	public:
		ExitingGameState(StateManager* stateManager);

		virtual void GetInput();
		virtual void Update();
		virtual void Display();

	private:
		bool m_messageDisplayed;
};