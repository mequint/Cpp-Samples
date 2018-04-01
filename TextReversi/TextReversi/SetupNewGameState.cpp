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
			std::cout << "1. Human vs. Human\n" << std::endl;
			//std::cout << "2. Human vs. AI\n";
			//std::cout << "3. AI vs. AI\n";
			std::cout << ": ";

			getMenuChoice();
			break;
		}

		case SetupNewGameStateCommands::HumanVsHuman:
		{
			// Determine player 1
			Player player1;
			player1.piece = getPlayerPiece();	// TODO: Does this function only get called here?
			player1.isHuman = true;
			m_stateManager->GetContext()->SetPlayer1(player1);

			// Determine player 2 - opposite of player 1
			Player player2;
			player2.piece = OppositePiece(player1.piece);
			player2.isHuman = true;
			m_stateManager->GetContext()->SetPlayer2(player2);

			m_stateManager->ChangeState(GameStateType::InGame);

			break;
		}

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

	if (line.length() == 1)
	{
		if (line == "1")
		{
			m_menuChoice = SetupNewGameStateCommands::HumanVsHuman;
		}
		/*
		else if (line == "2")
		{
		}
		else if (line == "3")
		{
		}
		*/
		else
		{
			m_menuChoice = SetupNewGameStateCommands::Invalid;
		}
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