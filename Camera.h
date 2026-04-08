#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(Scene* parentScene, float pixelScale);
	~Camera();

	SDL_Rect CalculateBounds(SDL_Rect& inputRect);
	Vector2 WorldToScreenPos(Vector2& pos);
	Vector2 ScreenToWorldPos(Vector2& pos);

private:
	float pixelScale;
};

