#pragma once

#include "Board.h"

char PieceOrAvailableMoveToChar(const Board& board, int row, int col, const std::vector<Cell>& availableMoves);
void DisplayBoard(const Board& board, const std::vector<Cell>& availableMoves = std::vector<Cell>());
void DisplayCurrentScore(const int xScore, const int oScore);
void DisplayWhoseTurn(Piece currentPlayer);