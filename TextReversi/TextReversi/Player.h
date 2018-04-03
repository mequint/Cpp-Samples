#pragma once

#include "Piece.h"

/*
AI Behaviors

Base Behavior is Human Player Behavior (currently in InGame state)
- Current Turn becomes current player...

For "random" AI behavior
- Retrieve the board
- Grab the vector of available moves
- Choose a move at random
- Place it in a "Move" struct and return

For "most pieces" AI behavior
- Grab the vector of available moves
- For every move
- Place a piece
- Get the resulting board score
- Store the highest score result and the move index
- Once every move has been checked, grab the index with the "best" move
- Place in in a "Move" struct and return
*/

class Player
{
	public:
		Piece GetPiece() const;
		void SetPiece(Piece piece);

		bool IsHuman() const;
		void SetIsHuman(bool isHuman);

	private:
		Piece m_piece;
		bool m_isHuman;
};