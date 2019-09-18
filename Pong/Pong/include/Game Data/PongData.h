#pragma once

enum class SpecialAbility {
	None = -1, Fireball, WaterWall, EarthBarrier, WindGust, SplitBall, COUNT
};

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