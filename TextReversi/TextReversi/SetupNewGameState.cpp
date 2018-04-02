#include "SetupNewGameState.h"

#include <iostream>

#include "Input.h"
#include "Player.h"
#include "StateManager.h"

SetupNewGameState::SetupNewGameState(StateManager* stateManager) :
	GameState(stateManager),
	m_menuChoice(SetupNewGameStateCommands::Unset)
{
}

void SetupNewGameState::Run()
{
	switch (m_menuChoice)
	{
		case SetupNewGameStateCommands::Unset:
		{
			std::cout << "\nNew Game Options\n";
			std::cout << "----------------\n\n";
			std::cout << "1. Human vs. Human\n";
			//std::cout << "2. Human vs. Computer\n";
			//std::cout << "3. Computer vs. Computer\n";
			std::cout << "4. Go Back\n\n";
			std::cout << ": ";

			getMenuChoice();
			break;
		}

		case SetupNewGameStateCommands::HumanVsHuman:
		{
			// Reset the game - just in case
			m_stateManager->GetContext()->Reset();

			// Determine player 1
			Player player1;
			player1.SetPiece(getPlayerPiece());
			player1.SetIsHuman(true);
			m_stateManager->GetContext()->SetPlayer1(player1);

			// Determine player 2 - opposite of player 1
			Player player2;
			player2.SetPiece(OppositePiece(player1.GetPiece()));
			player2.SetIsHuman(true);
			m_stateManager->GetContext()->SetPlayer2(player2);

			// Game On!!!
			m_stateManager->ChangeState(GameStateType::InGame);
			m_menuChoice = SetupNewGameStateCommands::Unset;

			break;
		}

		case SetupNewGameStateCommands::GoBack:
			m_stateManager->ChangeState(GameStateType::MainMenu);
			m_menuChoice = SetupNewGameStateCommands::Unset;
			break;

		case SetupNewGameStateCommands::Invalid:
		{
			std::cout << "\nInvalid option...\n";
			m_menuChoice = SetupNewGameStateCommands::Unset;
			break;
		}
	}
}

void SetupNewGameState::getMenuChoice()
{
	std::string line;
	getline(std::cin, line);

	if (line == "1")
	{
		m_menuChoice = SetupNewGameStateCommands::HumanVsHuman;
	}
	/*
	// Human vs Computer
	else if (line == "2")
	{
	}
	else if (line == "3")
	{
	}
	*/
	else if (line == "4")
	{
		m_menuChoice = SetupNewGameStateCommands::GoBack;
	}
	else
	{
		m_menuChoice = SetupNewGameStateCommands::Invalid;
	}
}

Piece SetupNewGameState::getPlayerPiece()
{
	char goFirst = AskYesOrNoQuestion("\nPlayer 1, would you like to go first?");

	if (tolower(goFirst) == 'y')
	{
		std::cout << "\nPlayer 1 is 'X' and Player 2 is 'O'\n\n";
		return Piece::X;
	}

	std::cout << "\nPlayer 1 is 'O' and Player 2 is 'X'\n\n";
	return Piece::O;
}