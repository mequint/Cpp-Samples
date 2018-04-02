#include "GameContext.h"

#include <fstream>
#include <iostream>
#include <string>

GameContext::GameContext() :
	totalMoves(4),
	currentTurn(Piece::X)
{
	Reset();
}

void GameContext::Reset()
{
	gameBoard.Reset();
	UpdateScore();
	totalMoves = 4;
}

bool GameContext::AreMovesAvailable()
{
	return gameBoard.AreMovesAvailable(currentTurn);
}

void GameContext::MakeMove(const int row, const int col)
{
	gameBoard.MakeMove(row, col, currentTurn);
	UpdateScore();
	totalMoves++;
}

void GameContext::UpdateScore()
{
	xScore = 0;
	oScore = 0;

	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			Piece piece = gameBoard.GetCell(row, col);

			if (piece == Piece::X)
				xScore++;
			else if (piece == Piece::O)
				oScore++;
		}
	}
}

// Mutators
void GameContext::SetPlayer1(const Player& player) { player1 = player; }
void GameContext::SetPlayer2(const Player& player) { player2 = player; }
void GameContext::SetCurrentTurn(const Piece& piece) { currentTurn = piece; }

// Accessors
Player GameContext::GetPlayer1() const { return player1; }
Player GameContext::GetPlayer2() const { return player2; }
int GameContext::GetXScore() const { return xScore; }
int GameContext::GetOScore() const { return oScore; }
int GameContext::GetTotalMoves() const { return totalMoves; }
Piece GameContext::GetCurrentTurn() const { return currentTurn; }
Board GameContext::GetBoard() const { return gameBoard; }

// Game File IO
bool GameContext::Save(const std::string& name)
{
	std::ofstream myFile;
	myFile.open(name);

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			myFile << PieceToChar(gameBoard.GetCell(i, j));
		}
		myFile << std::endl;
	}

	myFile << PieceToChar(currentTurn) << std::endl;
	myFile << PieceToChar(player1.GetPiece()) << " " << player1.IsHuman() << std::endl;
	myFile << PieceToChar(player2.GetPiece()) << " " << player2.IsHuman() << std::endl;

	return true;
}

bool GameContext::Load(const std::string& filename)
{
	std::ifstream myFile;
	myFile.open(filename);

	if (myFile.is_open())
	{
		Reset();

		// Load the board
		for (int i = 0; i < 8; ++i)
		{
			std::string line;
			getline(myFile, line);

			for (int j = 0; j < 8; ++j)
			{
				gameBoard.SetCell(i, j, CharToPiece(line[j]));
				totalMoves++;
			}
		}

		// Load the current turn
		char c;
		myFile >> c;
		currentTurn = CharToPiece(c);

		// Load player 1
		bool isHuman;
		myFile >> c >> isHuman;
		player1.SetPiece(CharToPiece(c));
		player1.SetIsHuman(isHuman);

		// Load player 2
		myFile >> c >> isHuman;
		player2.SetPiece(CharToPiece(c));
		player2.SetIsHuman(isHuman);

		// Update the score
		UpdateScore();

		return true;
	}

	return false;
}