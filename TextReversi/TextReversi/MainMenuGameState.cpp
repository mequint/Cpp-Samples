#include "MainMenuGameState.h"

#include <iostream>
#include <string>

#include "StateManager.h"

MainMenuGameState::MainMenuGameState(StateManager* stateManager) :
	GameState(stateManager),
	m_menuChoice(MainMenuCommands::UNSET)
{}

void MainMenuGameState::Run()
{
	switch (m_menuChoice)
	{
		case MainMenuCommands::UNSET:
			std::cout << "\nMAIN MENU\n";
			std::cout << "---------\n\n";
			std::cout << "Please select an option:\n";
			std::cout << "  1. New Game\n";
			std::cout << "  2. Load Game\n";
			std::cout << "  3. Display Instructions" << std::endl;
			std::cout << "  4. Exit" << std::endl << std::endl;

			std::cout << ": ";

			getMenuChoice();

			break;

		case MainMenuCommands::INVALID:
			std::cout << "\nInvalid option...\n\n";
			m_menuChoice = MainMenuCommands::UNSET;
			break;

		case MainMenuCommands::NEW_GAME:
			std::cout << "\nChanging to new game state...\n\n";
			m_menuChoice = MainMenuCommands::UNSET;
			break;

		case MainMenuCommands::LOAD_GAME:
			std::cout << "\nChanging to load game state...\n\n";
			m_menuChoice = MainMenuCommands::UNSET;
			break;

			// Call the state machine to set up the display instructions state
		case MainMenuCommands::DISPLAY_INSTRUCTIONS:
			m_stateManager->ChangeState(GameStateType::DisplayRules);
			m_menuChoice = MainMenuCommands::UNSET;
			break;

			// Call the state machine to run the exit state
		case MainMenuCommands::EXIT:
			std::cout << "\nChanging to exit game state...\n\n";
			m_stateManager->ChangeState(GameStateType::Exiting);
			m_menuChoice = MainMenuCommands::UNSET;
			break;
	}
}

void MainMenuGameState::getMenuChoice()
{
	std::string line;
	getline(std::cin, line);

	if (line.length() == 1)
	{
		if (line == "1")
		{
			m_menuChoice = MainMenuCommands::NEW_GAME;
		}
		else if (line == "2")
		{
			m_menuChoice = MainMenuCommands::LOAD_GAME;
		}
		else if (line == "3")
		{
			m_menuChoice = MainMenuCommands::DISPLAY_INSTRUCTIONS;
		}
		else if (line == "4")
		{
			m_menuChoice = MainMenuCommands::EXIT;
		}
		else
		{
			m_menuChoice = MainMenuCommands::INVALID;
		}
	}
	else
	{
		m_menuChoice = MainMenuCommands::INVALID;
	}
}
