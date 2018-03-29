#include "MainMenuGameState.h"

#include <iostream>
#include <string>

MainMenuGameState::MainMenuGameState() :
	promptEnabled(false),
	menuChoice(MainMenuCommands::UNSET),
	displayedError(false)
{

}

void MainMenuGameState::GetInput() 
{
	if (promptEnabled)
	{
		std::string line;
		getline(std::cin, line);

		if (line.length() == 1)
		{
			if (line == "1")
			{
				menuChoice = MainMenuCommands::NEW_GAME;
			}
			else if (line == "2")
			{
				menuChoice = MainMenuCommands::LOAD_GAME;
			}
			else if (line == "3")
			{
				menuChoice = MainMenuCommands::DISPLAY_INSTRUCTIONS;
			}
			else if (line == "4")
			{
				menuChoice = MainMenuCommands::EXIT;
			}
			else
			{
				menuChoice = MainMenuCommands::INVALID;
			}
		}
		else
		{
			menuChoice = MainMenuCommands::INVALID;
		}
	}
}

void MainMenuGameState::Update() 
{
	promptEnabled = false;

	switch (menuChoice)
	{
		case MainMenuCommands::UNSET:
			promptEnabled = true;
			break;

		// Call the state machine to set up the new game state
		case MainMenuCommands::NEW_GAME:
			break;

		// Call the state machine to set up the load game state
		case MainMenuCommands::LOAD_GAME:
			break;

		// Call the state machine to set up the display instructions state
		case MainMenuCommands::DISPLAY_INSTRUCTIONS:
			break;

		// Call the state machine to run the exit state
		case MainMenuCommands::EXIT:
			break;

		case MainMenuCommands::INVALID:
			if (!displayedError)
			{
				displayedError = true;
			}
			else
			{
				displayedError = false;
				menuChoice = MainMenuCommands::UNSET;
			}

			break;
	}
}

void MainMenuGameState::Display()
{
	switch (menuChoice)
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