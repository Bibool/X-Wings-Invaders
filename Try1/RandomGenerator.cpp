#include <ctime>
#include <random>
#include "RandomGenerator.h"

// Initialize the Messner Twister here
// My flawed implementation
std::random_device randomDevice;
std::mt19937 randomEngine(randomDevice());

RandomGenerator::RandomGenerator()
{
	
}

// Messner Twister Engine powered random number
// Returns a random number that is fed into it
int RandomGenerator::randomInt(int a, int b)
{
	std::uniform_int_distribution<int> randomPick(a, b);
	return randomPick(randomEngine);
}

// Zafs Random Class
// Refactored to use proper C++ style casting
namespace Random
{
	// Initializes the seed
	void initialiseSeed()
	{
		srand(static_cast<int>(time(nullptr)));
	}

	// Returns a random floating point number between 0 and 1
	float get01()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	// Returns a max value
	float get(float maxValue)
	{
		return get01() * maxValue;
	}

	// Returns a random number between Min and Max
	float get(float minValue, float maxValue)
	{
		return minValue + get01() * ( maxValue - minValue );
	}
}
