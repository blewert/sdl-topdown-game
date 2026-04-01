#pragma once
#include "Vector2.h"

class Scene;

class GameObject
{
public:
	GameObject(Scene* parentScene);
	void SetPosition(const Vector2& newPosition);
	Vector2 GetPosition();

private:
	Scene* parentScene;
	Vector2 position;
};

