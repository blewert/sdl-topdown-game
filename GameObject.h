#pragma once
#include "Vector2.h"

class Scene;

class GameObject
{
public:
	GameObject(Scene* parentScene);
	~GameObject();

	void SetPosition(const Vector2& newPosition);
	Vector2 GetPosition();

	virtual void OnStart() {};
	virtual void Update() {};
	virtual void OnEnd() {};

	void Destroy() { pendingDelete = true; }

	bool pendingDelete = false;
	int id;

private:
	Scene* parentScene;
	Vector2 position = Vector2::zero;

	static int objId;
};

