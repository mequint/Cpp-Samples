#pragma once

#include <string>

#include "Board.h"
#include "Piece.h"

char AskYesOrNoQuestion(std::string question);
int RequestMove();
Piece GetPlayerPiece();
int GetPlayerMove(Board& board, Piece currentPlayer);