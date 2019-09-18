#pragma once

#include <SFML/System/Mutex.hpp>
#include <random>

namespace qe {
	class RandomGenerator {
	public:
		RandomGenerator();

		int Generate(int min, int max);
		float Generate(float min, float max);

		int operator()(int min, int max);
		float operator()(float min, float max);

	private:
		std::random_device m_device;
		std::mt19937 m_engine;
		std::uniform_int_distribution<int> m_intDistribution;
		std::uniform_real_distribution<float> m_floatDistribution;

		sf::Mutex m_mutex;
	};
}