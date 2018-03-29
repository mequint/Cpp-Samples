#pragma once

enum class Piece
{
	X,
	O,
	EMPTY,
	INVALID
};

inline char PieceToChar(Piece piece)
{
	switch (piece)
	{
		case Piece::EMPTY:	return ' ';
		case Piece::O:		return 'O';
		case Piece::X:		return 'X';
	}

	// Some random invalid default character
	return '=';
}

inline Piece CharToPiece(char c)
{
	switch (c)
	{
		case 'O': return Piece::O;
		case 'X': return Piece::X;
	}

	return Piece::EMPTY;
}

inline Piece OppositePiece(Piece piece)
{
	return (piece == Piece::X) ? Piece::O : Piece::X;
}