#include "pch.h"
#include "Utilities.h"
#include <random>
#include <ctime>

int Utilities::get_random(int min, int max)
{
	std::default_random_engine generator;
	generator.seed(time(0));

	const std::uniform_int_distribution<int> distribution(min, max);

	return distribution(generator);
}
