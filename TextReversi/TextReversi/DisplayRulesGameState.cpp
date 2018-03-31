#include "DisplayRulesGameState.h"

#include <conio.h>
#include <iostream>

#include "StateManager.h"

DisplayRulesGameState::DisplayRulesGameState(StateManager* stateManager) :
	GameState(stateManager),
	promptEnabled(false),
	command(DisplayRulesGameStateCommands::UNSET)
{
}

void DisplayRulesGameState::GetInput() 
{
	if (promptEnabled)
	{
		_getch();
		command = DisplayRulesGameStateCommands::RETURN_HOME;
	}
}
void DisplayRulesGameState::Update()
{
	promptEnabled = false;

	switch (command)
	{
		case DisplayRulesGameStateCommands::RETURN_HOME:
			m_stateManager->ChangeState(GameStateType::MainMenu);
			break;

		case DisplayRulesGameStateCommands::UNSET:
			promptEnabled = true;
			break;
	}
}

void DisplayRulesGameState::Display()
{
	switch (command)
	{
		case DisplayRulesGameStateCommands::UNSET:
			std::cout << "The object of the game is to get more pieces than your opponent.\n\n";
			std::cout << "Place a piece on the board by pressing (a-h) followed by (1-8).\n";
			std::cout << "If any of your opponents pieces are in between the cell you selected\n";
			std::cout << "and any of your other pieces, your opponents pieces will be changed to\n";
			std::cout << "the color of your pieces.\n\n";
			std::cout << "Watch out your opponent, will do the same to you!\n\n";
			std::cout << "The game ends when the board is full or there are no more available moves.\n\n";

			std::cout << " a1 | a2 | a3 | a4 | a5 | a6 | a7 | a8 \n";
			std::cout << "---------------------------------------\n";
			std::cout << " b1 | b2 | b3 | b4 | b5 | b6 | b7 | b8 \n";
			std::cout << "---------------------------------------\n";
			std::cout << " c1 | c2 | c3 | c4 | c5 | c6 | c7 | c8 \n";
			std::cout << "---------------------------------------\n";
			std::cout << " d1 | d2 | d3 | d4 | d5 | d6 | d7 | d8 \n";
			std::cout << "---------------------------------------\n";
			std::cout << " e1 | e2 | e3 | e4 | e5 | e6 | e7 | e8 \n";
			std::cout << "---------------------------------------\n";
			std::cout << " f1 | f2 | f3 | f4 | f5 | f6 | f7 | f8 \n";
			std::cout << "---------------------------------------\n";
			std::cout << " g1 | g2 | g3 | g4 | g5 | g6 | g7 | g8 \n";
			std::cout << "---------------------------------------\n";
			std::cout << " h1 | h2 | h3 | h4 | h5 | h6 | h7 | h8 \n\n";

			std::cout << "Press any key to continue...\n\n";

			promptEnabled = true;
			break;

		case DisplayRulesGameStateCommands::RETURN_HOME:
			std::cout << "Returning to the Main Menu state...\n";
			break;
	}
}