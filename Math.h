#pragma once
#include <cmath>
#include <time.h>

namespace Math
{

}

namespace Random
{
	static inline void SeedRNG(unsigned int seed = 0)
	{
		srand(time((time_t*)seed));
	}

	static inline int Range(int a, int b)
	{
		return a + rand() % (b - a);
	}

	static inline float Value()
	{
		return rand() / (float)RAND_MAX;
	}

	static inline float Range(float a, float b)
	{
		float val = Random::Value();
		return a + val * (b - a);
	}
}
