#pragma once
#include <stdint.h>
#include "SDL.h"

namespace Time
{
	static uint64_t lastTickTime = 0;
	static float deltaTime = 0.0f;
	static uint64_t deltaTicks = 0L;

	static inline void Initialise()
	{
		lastTickTime = SDL_GetPerformanceCounter();
	}

	static float GetFPS()
	{
		return 1.0f / deltaTime;
	}

	static inline void Tick()
	{
		uint64_t now = SDL_GetPerformanceCounter();
		uint64_t delta = (now - lastTickTime);

		Time::deltaTicks = delta;
		Time::deltaTime = (now - Time::lastTickTime)*1000 / (float)SDL_GetPerformanceCounter();

		Time::lastTickTime = now;
	}
}