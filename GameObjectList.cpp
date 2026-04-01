#include "GameObjectList.h"
#include "GameObject.h"
#include "SDL.h"
#include <memory>

GameObjectList::GameObjectList()
{

}

GameObjectList::~GameObjectList()
{

}

void GameObjectList::Add(GameObject* obj)
{
	obj->OnStart();
	objects.push_back(obj);
}

void GameObjectList::OnStart()
{
	for (GameObject* obj : objects)
		obj->OnStart();
}

void GameObjectList::Update()
{
	for (GameObject* obj : objects)
		obj->Update();

	CullPendingDeleteObjects();
}

void GameObjectList::OnEnd()
{
	for (GameObject* obj : objects)
		obj->OnEnd();
}

void GameObjectList::Render(SDL_Renderer* renderer)
{
	for (GameObject* obj : objects)
		obj->Render(renderer);
}

void GameObjectList::CullPendingDeleteObjects()
{
	std::vector<GameObject*> tmpObjs;

	for (int i = 0; i < objects.size(); i++)
	{
		//If not pending delete, add to temp list
		if (!objects[i]->pendingDelete)
			tmpObjs.push_back(objects[i]);

		//Otherwise, call destructor: this will no longer exist
		else delete objects[i];
	}

	//Then swap the underlying values
	std::swap(this->objects, tmpObjs);
}
