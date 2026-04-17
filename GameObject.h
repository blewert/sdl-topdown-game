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

	virtual void SetPosition(const Vector2& newPosition);
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

	virtual void PostRender(SDL_Renderer* renderer)
	{
		if (this->renderer != nullptr)
			this->renderer->PostRender();
	}

	Renderer* GetRenderer() { return renderer;  }
	void Destroy() { pendingDelete = true; }

	bool pendingDelete = false;
	bool enabled = true;
	uint64_t id;

	Scene* parentScene;

	void SetName(const std::string& name) { this->name = name; }
	void SetTag(const std::string& tag) { this->tag = tag; }
	const std::string& GetTag() { return tag; }
	const std::string& GetName() { return name; }

protected:
	Vector2 position = Vector2::zero;
	ComponentList* components = nullptr;
	Renderer* renderer = nullptr;
	static uint64_t objId;

	std::string name;
	std::string tag;

	virtual void OnCollisionEnter(Rigidbody& thisRb, Rigidbody& otherRb);
	virtual void OnCollisionExit(Rigidbody& thisRb, Rigidbody& otherRb);
	virtual void OnCollisionStay(Rigidbody& thisRb, Rigidbody& otherRb);

	friend class Rigidbody;
	friend class GameObjectList;
	friend class Component;
};

