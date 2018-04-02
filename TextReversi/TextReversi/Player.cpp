#include "Player.h"

Piece Player::GetPiece() const { return m_piece; }
void Player::SetPiece(Piece piece) { m_piece = piece; }

bool Player::IsHuman() const { return m_isHuman; }
void Player::SetIsHuman(bool isHuman) { m_isHuman = isHuman; }