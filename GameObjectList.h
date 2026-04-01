#pragma once
#include <vector>
#include "GameObject.h"

class GameObjectList
{
public:
	GameObjectList();
	~GameObjectList();

	void Add(GameObject* obj);
	inline int Count() { return objects->size(); };

public:
	void OnStart();
	void Update();
	void OnEnd();
	
	//TODO: Implement IRenderable interface to make render method access
	//      a little easier
	void Render(SDL_Renderer* renderer);

private:
	//TODO: make this not heap alloc'd so the callee can choose
	std::vector<GameObject*>* objects;

	void CullPendingDeleteObjects();
};

