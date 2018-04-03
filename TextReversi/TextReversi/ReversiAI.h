#pragma once

#include "GameContext.h"
#include "InGameCommands.h"
#include "RandomNumberGenerator.h"

class ReversiAI
{
	public:
		Move RequestMove(GameContext* context);

	private:
		RandomNumberGenerator m_rng;
};