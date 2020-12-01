#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

class RandomGenerator
{
public:
	RandomGenerator();

	int randomInt(int a, int b);
};

namespace Random
{
	// Call once towards start of your program. Initialise the seed value randomly
	void initialiseSeed();

	// Get a pseudo-random number between 0.0f and 1.0f inclusive
	float get01();

	// Get a pseudo-random number between 0.0f and 'maxValue' inclusive
	float get(float maxValue);

	// Get a pseudo-random number between 'minValue' and 'maxValue' inclusive
	float get(float minValue, float maxValue);
}


#endif