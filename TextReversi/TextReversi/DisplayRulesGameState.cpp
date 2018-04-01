#include "DisplayRulesGameState.h"

#include <iostream>

#include "StateManager.h"

DisplayRulesGameState::DisplayRulesGameState(StateManager* stateManager) :
	GameState(stateManager)
{
}

void DisplayRulesGameState::Run()
{
	std::cout << "\n\nHow to Play Text Reversi\n";
	std::cout << "------------------------\n\n";

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

	m_stateManager->ChangeState(GameStateType::MainMenu);
}