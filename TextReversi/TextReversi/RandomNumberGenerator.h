#pragma once

#include <random>

class RandomNumberGenerator
{
	public:
		RandomNumberGenerator();

		int GetInt(int from, int to);

	private:
		std::random_device m_rd;
		std::mt19937 m_rng;
		std::uniform_int_distribution<int> randomPick;
};