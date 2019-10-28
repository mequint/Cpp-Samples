#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int numbers) : m_generator((std::random_device())()),m_index(0), m_numbers(numbers)
{
	Reset();
}

int RandomGenerator::GetNextInt()
{
	if (m_index == m_sequence.size())
	{
		m_index = 0;
		Shuffle();
	}

	return m_sequence[m_index++];
}

void RandomGenerator::Reset()
{
	m_sequence.clear();

	for (int i = 1; i <= m_numbers; ++i)
	{
		m_sequence.emplace_back(i);
	}

	Shuffle();
}

void RandomGenerator::Shuffle()
{
	std::sort(m_sequence.begin(), m_sequence.end());
	for (int i = m_sequence.size() - 1; i >= 0; --i)
	{
		std::uniform_int_distribution<int> dist(0, i);
		int index = dist(m_generator);

		int temp = m_sequence[i];
		m_sequence[i] = m_sequence[index];
		m_sequence[index] = temp;
	}
}