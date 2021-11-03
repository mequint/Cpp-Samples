#include "qe/Utilities/RandomGenerator.h"

#include <mutex>

qe::RandomGenerator::RandomGenerator() : m_generator((std::random_device())()) {
}

int qe::RandomGenerator::nextInt(int min, int max) {
	std::mutex lock;

	lock.lock();
	std::uniform_int_distribution<int> dist(min, max);
	int number = dist(m_generator);
	lock.unlock();

	return number;
}