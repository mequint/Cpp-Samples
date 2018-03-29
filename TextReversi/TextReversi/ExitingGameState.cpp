#include "ExitingGameState.h"

#include <iostream>

void ExitingGameState::GetInput() {}
void ExitingGameState::Update() {}

void ExitingGameState::Display()
{
	std::cout << "Thank you for playing! Good night!\n\n";
}