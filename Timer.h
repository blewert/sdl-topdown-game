#pragma once
#include "Time.h"

struct Timer
{
public:
	Timer() = default;
	Timer(float timerTarget) : timerTarget(timerTarget) {};

	bool Tick()
	{
		timer += Time::deltaTime;

		if (timer >= timerTarget)
		{
			timer = Time::deltaTime;
			return true;
		}

		return false;
	}

private:
	float timer;
	float timerTarget;
};

