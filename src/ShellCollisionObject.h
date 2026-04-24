#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Scene.h"
#include "VFXManager.h"

class ShellCollisionObject : public GameObject
{
public:

	int life = 3;

	ShellCollisionObject(const Vector2& position, float radius, Scene* parentScene) : GameObject(parentScene)
	{
		SetTag("shell");
		SetName("shell");

		Vector2 pos = position;
		pos.x -= radius / 2;
		pos.y -= radius / 2;

		pos = parentScene->GetCamera()->ScreenToWorldPos(pos);

		SetPosition(pos);

		components = new ComponentList();

		BoxCollider bc = BoxCollider(this, { 0, 0, radius, radius });
		components->Pop();
		Rigidbody* rb = new Rigidbody(this, bc);

		VFXManager::SpawnEffect(pos, "explosion-1", 12);
		parentScene->GetObjects()->AddRigidbody(rb);
	}

	virtual ~ShellCollisionObject()
	{
		SDL_Log("shell dtor");
		delete components;
		components = nullptr;
	}

	virtual void OnCollisionEnter(Rigidbody& thisObj, Rigidbody& otherObj)
	{
		Destroy();
	}

	void Render(SDL_Renderer* renderer) override
	{
		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		//components->rigidbody->DebugRender(renderer);
	}

	void Update() override
	{
		//Runs only once, and destroys itself
		if(!pendingDelete)
			components->Update();

		if (life-- <= 0)
		{
			Destroy();
		}
	}
};

