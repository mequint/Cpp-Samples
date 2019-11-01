#include "RandomGenerator.h"

#include <SFML/System/Lock.hpp>

RandomGenerator::RandomGenerator() : m_engine(m_device()) {
}

int RandomGenerator::Generate(int min, int max) {
	sf::Lock lock(m_mutex);

	if (min > max) {
		std::swap(min, max);
	}

	if (min != m_intDistribution.min() || max != m_intDistribution.max()) {
		m_intDistribution = std::uniform_int_distribution<int>(min, max);
	}

	return m_intDistribution(m_engine);
}

float RandomGenerator::Generate(float min, float max) {
	sf::Lock lock(m_mutex);

	if (min > max) {
		std::swap(min, max);
	}

	if (min != m_floatDistribution.min() || max != m_floatDistribution.max()) {
		m_floatDistribution = std::uniform_real_distribution<float>(min, max);
	}

	return m_floatDistribution(m_engine);
}

int RandomGenerator::operator()(int min, int max) {
	return Generate(min, max);
}

float RandomGenerator::operator()(float min, float max) {
	return Generate(min, max);
}