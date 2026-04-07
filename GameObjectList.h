#pragma once
#include <vector>
#include "GameObject.h"
#include "Rigidbody.h"

class GameObjectList
{
public:
	GameObjectList();
	~GameObjectList();

	void Add(GameObject* obj);
	void AddRigidbody(Rigidbody* rb);

	inline int Count() { return objects.size(); };

public:
	void OnStart();
	void Update();
	void OnEnd();
	
	//TODO: Implement IRenderable interface to make render method access
	//      a little easier
	void Render(SDL_Renderer* renderer);

private:
	std::vector<GameObject*> objects;
	std::vector<Rigidbody*> bodies;

	void CullPendingDeleteObjects();
};

