#pragma once

#include "Piece.h"
class Player
{
	public:
		Piece piece;
		bool isHuman;

		virtual void MakeMove() {}		// A human would use standard input, the AI would use a strategy to make a decision
};