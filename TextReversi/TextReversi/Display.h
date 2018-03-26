#pragma once

#include "Board.h"

void DisplayInstructions();
void DisplayBoard(const Board& board);
void DisplayCurrentScore(const Board& board, Piece player1, Piece player2, int turn);
void DisplayWhoseTurn(Piece currentPlayer);
void DisplayWinner(Piece player1, Piece player2, int finalX, int finalO);