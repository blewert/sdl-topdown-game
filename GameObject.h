#pragma once
#include "Vector2.h"
#include "Renderer.h"
#include "ComponentList.h"

class Camera;
class Scene;

class GameObject
{
public:
	GameObject(Scene* parentScene);
	~GameObject();

	void SetPosition(const Vector2& newPosition);
	Vector2 GetPosition();

	virtual void OnStart() {};

	virtual void Update()
	{
		if (components != nullptr)
			components->Update();
	};

	virtual void OnEnd() {};

	virtual void Render(SDL_Renderer* renderer)
	{
		if(this->renderer != nullptr)
			this->renderer->Update();

		if (this->renderer != nullptr)
			this->renderer->Render();
	};

	void Destroy() { pendingDelete = true; }

	bool pendingDelete = false;
	uint64_t id;

	Scene* parentScene;

protected:
	Vector2 position = Vector2::zero;
	ComponentList* components = nullptr;
	Renderer* renderer = nullptr;

	static uint64_t objId;
};

