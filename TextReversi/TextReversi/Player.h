#pragma once

#include "Piece.h"
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