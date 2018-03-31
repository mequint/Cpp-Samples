#include "MainMenuGameState.h"

#include <iostream>
#include <string>

#include "StateManager.h"

MainMenuGameState::MainMenuGameState(StateManager* stateManager) :
	GameState(stateManager),
	m_promptEnabled(false),
	m_menuChoice(MainMenuCommands::UNSET),
	m_messageDisplayed(false)
{

}

void MainMenuGameState::GetInput() 
{
	if (m_promptEnabled)
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
}

void MainMenuGameState::Update() 
{
	m_promptEnabled = false;

	switch (m_menuChoice)
	{
		case MainMenuCommands::UNSET:
			m_promptEnabled = true;
			break;

		// Call the state machine to set up the new game state
		case MainMenuCommands::NEW_GAME:
			m_menuChoice = MainMenuCommands::UNSET;
			break;

		// Call the state machine to set up the load game state
		case MainMenuCommands::LOAD_GAME:
			m_menuChoice = MainMenuCommands::UNSET;
			break;

		// Call the state machine to set up the display instructions state
		case MainMenuCommands::DISPLAY_INSTRUCTIONS:
			m_stateManager->ChangeState(GameStateType::DisplayRules);
			break;

		// Call the state machine to run the exit state
		case MainMenuCommands::EXIT:
			m_stateManager->ChangeState(GameStateType::Exiting);
			break;

		case MainMenuCommands::INVALID:
			if (!m_messageDisplayed)
			{
				m_messageDisplayed = true;
			}
			else
			{
				m_messageDisplayed = false;
				m_menuChoice = MainMenuCommands::UNSET;
			}

			break;
	}
}

void MainMenuGameState::Display()
{
	switch (m_menuChoice)
	{
		case MainMenuCommands::UNSET:
			std::cout << "Please select an option:\n";
			std::cout << "  1. New Game\n";
			std::cout << "  2. Load Game\n";
			std::cout << "  3. Display Instructions" << std::endl;
			std::cout << "  4. Exit" << std::endl << std::endl;

			std::cout << ": ";
			break;

		case MainMenuCommands::INVALID:
			std::cout << "Invalid option..." << std::endl << std::endl;
			break;

		case MainMenuCommands::NEW_GAME:
			std::cout << "Changing to new game state..." << std::endl;
			break;

		case MainMenuCommands::LOAD_GAME:
			std::cout << "Changing to load game state..." << std::endl;
			break;

			// Call the state machine to set up the display instructions state
		case MainMenuCommands::DISPLAY_INSTRUCTIONS:
			std::cout << "Changing to display instruction state..." << std::endl;
			break;

			// Call the state machine to run the exit state
		case MainMenuCommands::EXIT:
			std::cout << "Changing to exit game state..." << std::endl;
			break;
	}
}