#pragma once

#include "ShapeType.h"

struct GameData
{
	GameData()
	{
		Clear();
	}

	void Clear()
	{
		NewGame = true;
		Score = 0;
		Singles = 0;
		Doubles = 0;
		Triples = 0;
		Quadruples = 0;
		Combos = 0;
		LongestCombo = 0;

		Level = 0;

		for (int i = 0; i < (int)ShapeType::Count; ++i)
		{
			ShapeCount[i] = 0;
		}
	}

	// Start New Game? 
	bool NewGame;

	// Landing Statistics
	unsigned int Score;
	unsigned int Lines;
	unsigned int Singles;
	unsigned int Doubles;
	unsigned int Triples;
	unsigned int Quadruples;
	unsigned int Combos;
	unsigned int LongestCombo;
	
	unsigned int Level;

	// Shape Statistics
	unsigned int ShapeCount[(int)ShapeType::Count];
};