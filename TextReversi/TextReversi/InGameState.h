#pragma once

#include "GameContext.h"
#include "GameState.h"
#include "InGameCommands.h"
#include "ReversiAI.h"

class InGameState : public GameState
{
	public:
		InGameState(StateManager* stateManager);

		virtual void Run();

	private:
		bool m_gameOver;

		ReversiAI m_reversiAI;

		Move getPlayerMove();
		Move requestMove();

		bool IsAIPlayersTurn(GameContext* context, Piece currentPiece);

		void display(GameContext* context);
};	