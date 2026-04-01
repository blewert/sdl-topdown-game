#pragma once
#include <vector>

class GameObject;

class GameObjectList
{
public:
	GameObjectList();
	~GameObjectList();

	void Add(const GameObject& obj);

public:
	void OnStart();
	void Update();
	void OnEnd();

private:
	std::vector<GameObject>* objects;

	void CullPendingDeleteObjects();
};

