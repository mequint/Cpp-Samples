#pragma once

#include <random>

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

		// Random number gneration
		std::random_device m_rd;
		std::mt19937 m_rng;
		std::uniform_int_distribution<int> randomPick;

		Move getPlayerMove();
		Move requestMove();

		// AI moves
		Move requestMove(GameContext* context);
		bool IsAIPlayersTurn(GameContext* context, Piece currentPiece);

		void display(GameContext* context);
};	