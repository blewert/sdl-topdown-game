#pragma once
#include <cmath>
#include <time.h>
#include <limits>
#include "Vector2.h"

namespace Math
{
	static constexpr float epsilon = std::numeric_limits<float>().epsilon();

	static constexpr float degToRad = 0.0174533f;
	static constexpr float radToDeg = 1.0f / degToRad;

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
		srand(time(reinterpret_cast<time_t*>(seed)));
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

	static Vector2 PositionInRect(int x, int y, int w, int h)
	{
		float rX = Random::Range((float)x, (float)x + w);
		float rY = Random::Range((float)y, (float)y + h);

		return Vector2(rX, rY);
	}

	static Vector2 InUnitSquare()
	{
		float rX = Random::Range(0.0f, 1.0f);
		float rY = Random::Range(0.0f, 1.0f);

		return Vector2(rX, rY);
	}

	static Vector2 OnUnitCircle()
	{
		float rA = Random::Range(0.0f, 360.0f * Math::degToRad);

		return Vector2(sinf(rA) * 1.0f, cosf(rA) * 1.0f);
	}

	static SDL_Color Color()
	{
		SDL_Color col;
		col.r = Random::Range(0, 0xff);
		col.g = Random::Range(0, 0xff);
		col.b = Random::Range(0, 0xff);
		col.a = 0xff;

		return col;
	}

	static Vector2 InUnitCircle()
	{
		return Random::OnUnitCircle() * Random::Value();
	}
}
