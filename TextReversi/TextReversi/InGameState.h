#pragma once

#include "GameContext.h"
#include "GameState.h"

enum class InGameCommands
{
	Move,
	Save,
	Load,
	Quit,
	PrintBoard,
	Options
};

struct Move
{
	InGameCommands Command;
	int Row;
	int Col;
};

class InGameState : public GameState
{
	public:
		InGameState(StateManager* stateManager);

		virtual void Run();

	private:
		bool m_gameOver;

		Move getPlayerMove();
		Move requestMove();

		void display(GameContext* context);
};	