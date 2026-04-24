#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(Scene* parentScene, float pixelScale);
	~Camera();

	virtual void Update() override;

	SDL_FRect CalculateBounds(SDL_FRect& inputRect);
	Vector2 WorldToScreenPos(const Vector2& pos);
	Vector2 ScreenToWorldPos(const Vector2& pos);

	float GetPixelScale() { return pixelScale;  }

	virtual void SetPosition(const Vector2& newPosition) override;
	Vector2 LookAtPos(const Vector2& position);

private:
	float pixelScale;
	int windowW, windowH;

	Vector2 GetCameraCentreOffsetWorld();
};

