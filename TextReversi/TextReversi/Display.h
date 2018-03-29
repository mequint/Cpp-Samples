#pragma once

#include "Board.h"

void DisplayInstructions();
void DisplayBoard(const Board& board);
void DisplayCurrentScore(const int xScore, const int oScore);
void DisplayWhoseTurn(Piece currentPlayer);
void DisplayWinner(Piece player1, Piece player2, int finalX, int finalO);