#pragma once

#include <random>

class Random
{
	public:
		Random();

		int GetInt(int min, int max);

	private:
		std::mt19937 m_rng;
};