#pragma once

#include "GameState.h"

class IntroGameState : public GameState
{
	public:
		virtual void GetInput();
		virtual void Update();
		virtual void Display();
};