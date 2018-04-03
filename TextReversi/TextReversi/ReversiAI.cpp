#include "ReversiAI.h"

#include <chrono>
#include <thread>

#include "Board.h"

Move ReversiAI::RequestMove(GameContext * context)
{
	Board board = context->GetBoard();
	std::vector<Cell> moves = board.GetAvailableMoves(context->GetCurrentTurn());

	//- Choose a move at random
	int index = m_rng.GetInt(0, (int)moves.size() - 1);

	//- Place it in a "Move" struct and return
	Move move;
	move.Command = InGameCommands::Move;
	move.Row = moves[index].Row;
	move.Col = moves[index].Col;

	// Wait for a second before making the move
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return move;
}
