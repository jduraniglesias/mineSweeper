#include "Random.h"
#include <ctime>
std::mt19937 Random::random(time(0));

int Random::Int(int min, int max) {
	std::uniform_int_distribution<int> rand(min, max);
	return rand(random);
}