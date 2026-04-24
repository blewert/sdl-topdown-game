#pragma once
#include "SDL.h"
#include "Camera.h"
#include "GameObjectList.h"

class Camera;

class Scene
{
public:
	Scene(SDL_Renderer* renderer) : renderer(renderer) { }

	virtual void OnStart() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() { };
	virtual void OnEnd() = 0;
	virtual void Exit() = 0;

	virtual void Reset()
	{
		delete objects;
		objects = nullptr;
	}

	SDL_Renderer* GetRenderer() { return renderer; }

	Camera* GetCamera() { return camera; }
	void SetCamera(Camera* camera) { this->camera = camera; }

	void AddObject(GameObject* obj)
	{
		objects->pendingAddObjects.push_back(obj);
	}

protected:
	SDL_Renderer* renderer;
	GameObjectList* objects = nullptr;
	Camera* camera = nullptr;
	

public:
	GameObjectList* GetObjects()
	{
		return objects;
	}
};

