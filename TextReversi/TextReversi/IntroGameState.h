#pragma once

#include "GameState.h"

class IntroGameState : public GameState
{
	public:
		IntroGameState(StateManager* stateManager);

		virtual void GetInput();
		virtual void Update();
		virtual void Display();

	private:
		bool m_messageDisplayed;
};