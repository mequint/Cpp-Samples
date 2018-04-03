#include "ReversiAI.h"

#include <chrono>
#include <thread>

#include "Board.h"

Move ReversiAI::RequestMove(GameContext * context)
{
	Board board = context->GetBoard();
	std::vector<Cell> moves = board.GetAvailableMoves(context->GetCurrentTurn());

	Move move;
	move.Command = InGameCommands::Move;

	// Take the first available corner if available
	for (Cell cell : moves)
	{
		if (isCorner(cell))
		{
			move.Row = cell.Row;
			move.Col = cell.Col;

			// Wait for a second before making the move
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			return move;
		}
	}

	//- Choose a cell at random
	int index = m_rng.GetInt(0, (int)moves.size() - 1);
	move.Row = moves[index].Row;
	move.Col = moves[index].Col;

	// Wait for a second before making the move
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return move;
}

bool ReversiAI::isCorner(Cell cell)
{
	int row = cell.Row;
	int col = cell.Col;

	bool isCorner =
		(cell.Row == 0 && cell.Col == 0) || (cell.Row == 0 && cell.Col == 7) ||
		(cell.Row == 7 && cell.Col == 0) || (cell.Row == 7 && cell.Col == 7);

	if (isCorner) return true;

	return false;
}
