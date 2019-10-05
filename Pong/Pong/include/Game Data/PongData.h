#pragma once

#include "SpecialAbility.h"

struct PlayerData {
	int CurrentHealth;
	int MaxHealth;
	int CurrentSpecialPoints;
	int MaxSpecialPoints;

	SpecialAbility Special;
};

class PongData {
public:
	PongData();

	void Reset();

private:
	PlayerData m_leftPlayer;
	PlayerData m_rightPlayer;
};