#pragma once
#include "SDL.h"

struct Time
{
	static uint64_t lastTickTime;
	static float deltaTime;
	static uint64_t deltaTicks;
	static double elapsedTime;

	static inline void Initialise()
	{
		lastTickTime = SDL_GetPerformanceCounter();
	}

	static float GetFPS()
	{
		return (float)SDL_GetPerformanceFrequency() / (float)Time::deltaTicks;
	}

	static inline void Tick()
	{
		uint64_t now = SDL_GetPerformanceCounter();
		uint64_t delta = (now - lastTickTime);

		Time::deltaTicks = delta;
		Time::deltaTime = (delta) / (float)SDL_GetPerformanceFrequency();

		Time::lastTickTime = now;

		elapsedTime += Time::deltaTime;
	}
};