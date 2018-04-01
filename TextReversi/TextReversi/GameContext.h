#pragma once

#include "Board.h"
#include "Player.h"

class GameContext
{
	public:
		GameContext();

		void Reset();

		bool AreMovesAvailable();
		void MakeMove(int row, int col);
		void UpdateScore();

		void SetPlayer1(const Player& player);
		void SetPlayer2(const Player& player);

		int GetXScore() const;
		int GetOScore() const;

		int GetTotalMoves() const;

		void SetCurrentTurn(const Piece& piece);
		Piece GetCurrentTurn() const;

		Board GetBoard() const;

		bool Save(const std::string& filename);
		bool Load(const std::string& filename);

		// Shared context
		bool IsRunning() const;

	private:
		Board gameBoard;

		Player player1, player2;

		int xScore, oScore;
		int totalMoves;
		Piece currentTurn;

		bool m_isRunning;
};