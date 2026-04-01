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

private:
	std::vector<GameObject*>* objects;

	void CullPendingDeleteObjects();
};

