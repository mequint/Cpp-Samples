#include "Random.h"

Random::Random()
{
	m_rng.seed(std::random_device()());
}

int Random::GetInt(int min, int max)
{
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(m_rng);
}