#pragma once

#include "GameState.h"

class ExitingGameState : public GameState
{
	public:
		virtual void GetInput();
		virtual void Update();
		virtual void Display();
};