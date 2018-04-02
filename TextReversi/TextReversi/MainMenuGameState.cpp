#include "MainMenuGameState.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "StateManager.h"

MainMenuGameState::MainMenuGameState(StateManager* stateManager) :
	GameState(stateManager),
	m_menuChoice(MainMenuCommands::Unset)
{}

void MainMenuGameState::Run()
{
	switch (m_menuChoice)
	{
		case MainMenuCommands::Unset:
			std::cout << "\nMAIN MENU\n";
			std::cout << "---------\n\n";
			std::cout << "Please select an option:\n";
			std::cout << "  1. New Game\n";
			std::cout << "  2. Load Game\n";
			std::cout << "  3. Display Instructions\n";
			std::cout << "  4. Exit\n\n";

			std::cout << ": ";

			getMenuChoice();
			break;

		case MainMenuCommands::Invalid:
			std::cout << "\nInvalid option...\n\n";
			m_menuChoice = MainMenuCommands::Unset;
			break;

		case MainMenuCommands::NewGame:
			m_stateManager->ChangeState(GameStateType::SetupNewGame);
			m_menuChoice = MainMenuCommands::Unset;
			break;

		case MainMenuCommands::LoadGame:
			m_stateManager->ChangeState(GameStateType::LoadGame);
			m_menuChoice = MainMenuCommands::Unset;
			break;

		case MainMenuCommands::DisplayInstructions:
			m_stateManager->ChangeState(GameStateType::DisplayRules);
			m_menuChoice = MainMenuCommands::Unset;
			break;

		case MainMenuCommands::Exit:
			m_stateManager->ChangeState(GameStateType::Exiting);
			m_menuChoice = MainMenuCommands::Unset;
			break;
	}
}

void MainMenuGameState::getMenuChoice()
{
	std::string line;
	getline(std::cin, line);

	std::transform(line.begin(), line.end(), line.begin(), ::tolower);
	if (line == "1" || line == "new")
	{
		m_menuChoice = MainMenuCommands::NewGame;
	}
	else if (line == "2" || line == "load")
	{
		m_menuChoice = MainMenuCommands::LoadGame;
	}
	else if (line == "3" || line == "instructions")
	{
		m_menuChoice = MainMenuCommands::DisplayInstructions;
	}
	else if (line == "4" || line == "exit" || line == "quit")
	{
		m_menuChoice = MainMenuCommands::Exit;
	}
	else
	{
		m_menuChoice = MainMenuCommands::Invalid;
	}
}
