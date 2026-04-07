#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(Scene* parentScene, float pixelScale);
	~Camera();

	SDL_Rect CalculateBounds(SDL_Rect& inputRect);

private:
	float pixelScale;
};

