#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "Piece.h"

// Bugs (to fix):
//		Replace Line 51 with getline call - and parse out the 2 values manually
//		In the flip pieces method make sure that the j values aren't causing the next index to move one row up or down (erroneous behavior)

// TODO:
//		Put the board vector into its own class and move board specific behavior into it
//		Verify Lines 62-75 (the input processing steps) - make sure I'm not duplicating code

void DisplayInstructions();
char AskYesOrNoQuestion(std::string question);
int RequestMove();
Piece GetPlayerPiece();
Piece GetOpponentPiece(Piece piece);
void DisplayBoard(const std::vector<Piece>& board);
void DisplayCurrentScore(const std::vector<Piece>& board, Piece player1, Piece player2, int turn);
void DisplayWhoseTurn(Piece currentPlayer);

int PlayerMove(std::vector<Piece>& board, Piece currentPlayer);
void AnnounceWinner(const std::vector<Piece>& board, Piece player1, Piece player2, int finalX, int finalO);

bool IsMoveLegal(std::vector<Piece>& board, int cellIndex, Piece currentPiece);
bool CheckValidMoves(std::vector<Piece>& board, int cellIndex, Piece currentPiece);
void FlipPieces(std::vector<Piece>& board, int cellIndex, Piece currentPiece);

int main()
{
	int move = 0;
	int totalMoves = 4;
	char again = 'y';

	const int NUM_SQUARES = 64;

	DisplayInstructions();

	while (again == 'y')
	{
		// initialize the board
		std::vector<Piece> board(NUM_SQUARES, Piece::EMPTY);
		board[27] = Piece::X;
		board[28] = Piece::O;
		board[35] = Piece::O;
		board[36] = Piece::X;

		// determine who gets to play the piece
		Piece player1 = GetPlayerPiece();
		Piece player2 = GetOpponentPiece(player1);

		Piece currentTurn = Piece::X;
		DisplayBoard(board);
		DisplayCurrentScore(board, player1, player2, totalMoves);
		DisplayWhoseTurn(currentTurn);

		while (totalMoves < 64)
		{
			if (currentTurn == player1)
			{
				move = PlayerMove(board, player1);

				board[move] = player1;
				FlipPieces(board, move, player1);
			}
			else
			{
				move = PlayerMove(board, player2);

				board[move] = player2;
				FlipPieces(board, move, player2);
			}

			totalMoves++;
			currentTurn = GetOpponentPiece(currentTurn);

			DisplayBoard(board);
			DisplayCurrentScore(board, player1, player2, totalMoves);
			
			DisplayWhoseTurn(currentTurn);
		}

		DisplayCurrentScore(board, player1, player2, totalMoves);

		again = AskYesOrNoQuestion("Would you like to play again?");

	}

	std::cout << "Thank you for playing! Good night!" << std::endl;
	return 0;
}

void DisplayInstructions()
{
	char response;

	std::cout << "Welcome to TextReversi\n";

	response = AskYesOrNoQuestion("Would you like to read the instructions?");
	if (response == 'y')
	{
		std::cout << "Try to get more pieces than your opponent by selecting a spot\n";
		std::cout << "on the board that has my pieces between one or more\n";
		std::cout << "of your other pieces by selecting a letter(a-h)\n";
		std::cout << "followed by a number (1-8) that corresponds to the\n";
		std::cout << "following grid.\n\n";

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
	}

	std::cout << "Let the game begin!\n\n";
}

char AskYesOrNoQuestion(std::string question)
{
	char response;

	do
	{
		std::cout << question << " (y/n): ";
		std::cin >> response;

		response = tolower(response);
	} while (response != 'y' && response != 'n');

	return response;
}

int RequestMove()
{
	char letter;
	int rowValue;
	int columnValue;
	int move;

	do
	{
		std::cout << "Please enter a letter (a-h), then a number(1-8): ";
		std::cin >> letter >> columnValue;

		letter = tolower(letter);

		if (letter >= 'a' && letter <= 'h')
		{
			// Conver the letter into a cell value
			rowValue = (int)(letter - 'a') * 8;
		}
		else
		{
			std::cout << "Invalid letter." << std::endl;
		}
	} while (letter < 'a' && letter > 'h');

	move = rowValue + columnValue - 1;

	return move;
}

Piece GetPlayerPiece()
{
	char goFirst = AskYesOrNoQuestion("Player 1, would you like to go first?");

	if (tolower(goFirst) == 'y')
	{
		std::cout << "\nPlayer 1 is 'X' and Player 2 is 'O'\n";
		return Piece::X;
	}

	std::cout << "\nPlayer 1 is 'O' and Player 2 is 'X'\n";
	return Piece::O;
}

Piece GetOpponentPiece(Piece piece)
{
	return (piece == Piece::X) ? Piece::O : Piece::X;
}

void DisplayBoard(const std::vector<Piece>& board)
{
	std::cout << "\n  1   2   3   4   5   6   7   8 ";
	for (int i = 0; i < 8; ++i)
	{
		bool first = true;
		std::cout << "\n" << (char)(i + 'a');
		for (int j = 0; j < 8; ++j)
		{
			int index = i * 8 + j;

			std::cout << " " << PieceToChar(board[index]) << " ";

			if (j != 7)
			{
				std::cout << "|";
			}
		}

		if (i != 7)
		{
			std::cout << "\n--------------------------------";
		}
	}
	std::cout << std::endl;
}

void DisplayCurrentScore(const std::vector<Piece>& board, Piece player1, Piece player2, int turn)
{
	int xCount = 0;
	int oCount = 0;

	for (auto piece : board)
	{
		if (piece == Piece::X)
			xCount++;
		else if (piece == Piece::O) 
			oCount++;
	}

	std::cout << std::endl << "X = " << xCount << "\tO = " << oCount;

	if (turn >= 64)
	{
		AnnounceWinner(board, player1, player2, xCount, oCount);
	}
}

void DisplayWhoseTurn(Piece currentPlayer)
{
	char player = PieceToChar(currentPlayer);
	std::cout << "\t" << "It is " << player << "s turn" << std::endl << std::endl;
}

int PlayerMove(std::vector<Piece>& board, Piece currentPlayer)
{
	int move = RequestMove();

	while (!IsMoveLegal(board, move, currentPlayer))
	{
		std::cout << std::endl << "Invalid move." << std::endl;
		move = RequestMove();
	}

	return move;
}

void AnnounceWinner(const std::vector<Piece>& board, Piece player1, Piece player2, int finalX, int finalO)
{
	if (finalX > finalO)
	{
		std::string winner = (player1 == Piece::X) ? "Player 1" : "Player 2";
		std::cout << winner << " wins!" << std::endl;
	}
	else if (finalX < finalO)
	{
		std::string winner = (player1 == Piece::O) ? "Player 1" : "Player 2";
		std::cout << winner << " wins!" << std::endl;
	}
	else
	{
		std::cout << "The game was a draw..." << std::endl;
	}
}

bool IsMoveLegal(std::vector<Piece>& board, int cellIndex, Piece currentPiece)
{
	// Illegal move if the cell isn't empty
	if (board[cellIndex] != Piece::EMPTY) return false;

	bool anyMovesAvailable = CheckValidMoves(board, cellIndex, currentPiece);
	
	return anyMovesAvailable;
}

bool CheckValidMoves(std::vector<Piece>& board, int cellIndex, Piece currentPiece)
{
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0) continue;

			Piece opponentPiece = GetOpponentPiece(currentPiece);
			
			int cellMove = i * 8 + j;
			
			int nextIndex = cellIndex + cellMove;

			bool outOfBounds = (nextIndex < 0 || nextIndex > board.size() - 1);

			while (!outOfBounds && board[nextIndex] == opponentPiece)
			{
				nextIndex += cellMove;

				// Check for out of bounds
				outOfBounds = (nextIndex < 0 || nextIndex > board.size() - 1);

				// We have found a valid move
				if (!outOfBounds && board[nextIndex] == currentPiece)
					return true;
			}
		}
	}
		
	return false;
}

void FlipPieces(std::vector<Piece>& board, int cellIndex, Piece currentPiece)
{
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0) continue;

			Piece opponentPiece = GetOpponentPiece(currentPiece);

			int cellMove = i * 8 + j;
			int nextIndex = cellIndex + cellMove;

			bool outOfBounds = (nextIndex < 0 || nextIndex > board.size() - 1);

			std::stack<int> cellIndices;
			while (!outOfBounds && board[nextIndex] == opponentPiece)
			{
				cellIndices.push(nextIndex);

				nextIndex += cellMove;
				outOfBounds = (nextIndex < 0 || nextIndex > board.size() - 1);

				if (!outOfBounds && board[nextIndex] == currentPiece)
				{
					while (!cellIndices.empty())
					{
						int index = cellIndices.top();
						cellIndices.pop();

						board[index] = currentPiece;
					}
				}
			}
		}
	}
}