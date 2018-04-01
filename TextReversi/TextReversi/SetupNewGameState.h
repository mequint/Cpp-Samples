#pragma once

#include "GameState.h"
#include "Piece.h"

enum class SetupNewGameStateCommands
{
	Unset,
	HumanVsHuman,
	HumanVsAI,
	AIvsAi,
	Invalid
};

class SetupNewGameState : public GameState
{
	public:
		SetupNewGameState(StateManager* stateManager);

		virtual void Run();

	private:
		SetupNewGameStateCommands m_menuChoice;

		void getMenuChoice();
		Piece getPlayerPiece();
};