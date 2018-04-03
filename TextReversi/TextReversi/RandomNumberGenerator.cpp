#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator() :
	m_rng(m_rd())
{}

int RandomNumberGenerator::GetInt(int from, int to)
{
	std::uniform_int_distribution<int> choice(from, to);
	return choice(m_rng);
}
