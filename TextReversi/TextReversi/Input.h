#pragma once

#include <string>

#include "Board.h"
#include "Piece.h"

char AskYesOrNoQuestion(std::string question);
Move RequestMove();
Piece GetPlayerPiece();
Move GetPlayerMove(Board& board, Piece currentPlayer);