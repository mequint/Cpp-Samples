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

	MoveScore moveCheck = getBestMove(board, context->GetCurrentTurn(), context->GetCurrentTurn(), 4, 0);

	move.Row = moveCheck.Move.Row;
	move.Col = moveCheck.Move.Col;

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

// A mini-max check that scores a move based on the number of moves available afterwards
// The idea is that you want the maximum number of moves available while preventing your opponent from being able to move
MoveScore ReversiAI::getBestMove(Board board, Piece initialPlayer, Piece currentPlayer, int maxDepth, int currentDepth)
{
	if (!board.AreMovesAvailable(currentPlayer) || currentDepth == maxDepth)
	{
		MoveScore result;
		result.Score = (int)board.GetAvailableMoves(currentPlayer).size();

		return result;
	}

	MoveScore bestResult;
	bestResult.Score = (initialPlayer == currentPlayer) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

	for (auto cell : board.GetAvailableMoves(currentPlayer))
	{
		board.MakeMove(cell.Row, cell.Col, currentPlayer);

		auto currentResult = getBestMove(board, initialPlayer, OppositePiece(currentPlayer), maxDepth, currentDepth + 1);

		if (currentPlayer == initialPlayer)
		{
			if (currentResult.Score > bestResult.Score)
			{
				bestResult.Score = currentResult.Score;
				bestResult.Move.Row = cell.Row;
				bestResult.Move.Col = cell.Col;
			}
		}
		else
		{
			if (currentResult.Score < bestResult.Score)
			{
				bestResult.Score = currentResult.Score;
				bestResult.Move.Row = cell.Row;
				bestResult.Move.Col = cell.Col;
			}
		}
	}

	return bestResult;
}