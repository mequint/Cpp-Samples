#pragma once

#include "Board.h"
#include "Player.h"

class Game
{
	public:
		Game();

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

	private:
		Board gameBoard;

		Player player1, player2;

		int xScore, oScore;
		int totalMoves;
		Piece currentTurn;
};