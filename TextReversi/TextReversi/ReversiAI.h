#pragma once

#include "GameContext.h"
#include "InGameCommands.h"

struct MoveScore
{
	MoveScore() {}

	int Score;
	Cell Move;
};

class ReversiAI
{
	public:
		Move RequestMove(GameContext* context);

	private:
		bool isCorner(Cell cell);
		MoveScore getBestMove(Board board, Piece initialPlayer, Piece currentPlayer, int maxDepth, int currentDepth);
};