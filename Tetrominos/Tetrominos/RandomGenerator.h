#pragma once

#include <random>
#include <vector>

class RandomGenerator
{
	public:
		RandomGenerator(int numbers);

		int GetNextInt();

	private:
		void Shuffle();

		std::mt19937 m_generator;

		std::vector<int> m_sequence;
		int m_index;
};