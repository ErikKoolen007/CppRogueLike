#include "Utilities.h"
#include <random>
#include <chrono>

int Utilities::get_random(int min, int max)
{
	const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);

	const std::uniform_int_distribution<int> distribution(min, max);

	return distribution(generator);
}
