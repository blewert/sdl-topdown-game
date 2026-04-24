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

	GameObject* FindFirstObjectByName(const std::string& name);
	GameObject* FindFirstObjectByTag(const std::string& tag);
	std::vector<GameObject*> FindAllObjectsByName(const std::string& name);
	std::vector<GameObject*> FindAllObjectsByTag(const std::string& tag);

	inline int Count() { return objects.size(); };

public:
	void OnStart();
	void Update();
	void OnEnd();
	
	
	
	//TODO: Implement IRenderable interface to make render method access
	//      a little easier
	void Render(SDL_Renderer* renderer);
	void PostRender(SDL_Renderer* renderer);

private:
	std::vector<GameObject*> objects;
	std::vector<Rigidbody*> bodies;

	std::vector<GameObject*> pendingAddObjects;

	void CullPendingDeleteObjects();
	void CullPendingDeleteRBs();

	friend class Scene;
};

