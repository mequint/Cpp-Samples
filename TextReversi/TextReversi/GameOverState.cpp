#include "GameOverState.h"

#include <iostream>
#include <string>

#include "Display.h"
#include "Input.h"
#include "StateManager.h"

GameOverState::GameOverState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void GameOverState::Run()
{
	std::cout << std::endl;

	auto context = m_stateManager->GetContext();

	int finalX = context->GetXScore();
	int finalO = context->GetOScore();
	
	std::cout << "!!! GAME OVER !!!\n";
	DisplayCurrentScore(context->GetXScore(), context->GetOScore());

	if (finalX > finalO)
	{
		std::string winner = (context->GetPlayer1().GetPiece() == Piece::X) ? "\tPlayer 1" : "\tPlayer 2";
		std::cout << winner << " (X) wins!\n\n";
	}
	else if (finalX < finalO)
	{
		std::string winner = (context->GetPlayer1().GetPiece() == Piece::O) ? "\tPlayer 1" : "\tPlayer 2";
		std::cout << winner << " (O) wins!\n";
	}
	else
	{
		std::cout << "\tThe game was a draw...\n";
	}

	char again;
	do
	{
		again = AskYesOrNoQuestion("\nWould you like to play again?");
	} while (again != 'y' && again != 'n');

	if (again == 'y')
	{
		context->Reset();
		m_stateManager->ChangeState(GameStateType::SetupNewGame);
	}
	else
	{
		m_stateManager->ChangeState(GameStateType::MainMenu);
	}
}