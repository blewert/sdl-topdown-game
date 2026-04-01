#pragma once
#include <cmath>
#include <time.h>
#include <limits>

namespace Math
{
	static const float epsilon = std::numeric_limits<float>().epsilon();

	//Stolen from Unity's Mathf library
	//<https://github.com/Unity-Technologies/UnityCsReference/blob/master/Runtime/Export/Math/Mathf.cs>
	//(See Approximately)
	static inline bool Approximately(float lhs, float rhs)
	{
		float maxLR = fmaxf(lhs, rhs);
		float max = fmaxf(0.000001f * maxLR, epsilon * 8);
		return fabsf(rhs - lhs) <= max;
	}
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
