#include "GameObjectList.h"
#include "GameObject.h"

GameObjectList::GameObjectList()
{
	objects = new std::vector<GameObject>();
}

GameObjectList::~GameObjectList()
{
	delete[] objects;
}

void GameObjectList::Add(const GameObject& obj)
{
	objects->push_back(obj);
}

void GameObjectList::OnStart()
{
	for (GameObject& obj : *objects)
		obj.OnStart();
}

void GameObjectList::Update()
{
	for (GameObject& obj : *objects)
		obj.Update();
}

void GameObjectList::OnEnd()
{
	for (GameObject& obj : *objects)
		obj.OnEnd();
}

void GameObjectList::CullPendingDeleteObjects()
{

}
