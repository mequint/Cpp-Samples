#pragma once

#include <random>
#include <vector>

namespace qe {
	class RandomGenerator
	{
		public:
			RandomGenerator();

			int nextInt(int min, int max);

		private:
			std::mt19937 m_generator;

			std::vector<int> m_sequence;
			int m_index;
			int m_numbers;
	};
}