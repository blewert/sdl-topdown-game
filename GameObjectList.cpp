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

void GameObjectList::AddRigidbody(Rigidbody* rb)
{
	rb->parent->components->rigidbody = rb;
	//rb->parent->components->Add(rb);
	bodies.push_back(rb);
}

GameObject* GameObjectList::FindFirstObjectByName(const std::string& name)
{
	for (GameObject* obj : this->objects)
	{
		if (obj->name == name)
			return obj;
	}

	return nullptr;
}

GameObject* GameObjectList::FindFirstObjectByTag(const std::string& tag)
{
	for (GameObject* obj : this->objects)
	{
		if (obj->tag == tag)
			return obj;
	}

	return nullptr;
}

std::vector<GameObject*> GameObjectList::FindAllObjectsByName(const std::string& name)
{
	std::vector<GameObject*> objs;

	for (GameObject* obj : this->objects)
	{
		if (obj->name == name)
			objs.push_back(obj);
	}

	return objs;
}

std::vector<GameObject*> GameObjectList::FindAllObjectsByTag(const std::string& tag)
{
	std::vector<GameObject*> objs;

	for (GameObject* obj : this->objects)
	{
		if (obj->tag == tag)
			objs.push_back(obj);
	}

	return objs;
}

void GameObjectList::OnStart()
{
	for (GameObject* obj : objects)
		obj->OnStart();
}

void GameObjectList::Update()
{
	bool needsCull = false;

	for (GameObject* obj : objects)
	{
		obj->Update();
		
		if (obj->pendingDelete)
			needsCull = true;
	}

	//TODO: Spatial hashing here, this is 
	//      a bit intensive
	for (Rigidbody* a : bodies)
	{
		if (a->parent->pendingDelete)
			continue;

		for (Rigidbody* b : bodies)
		{
			if (b->parent->pendingDelete)
				continue;

			if (a == b)
				continue;

			if (Rigidbody::IsCollidingAABB(*a, *b))
			{
				//SDL_Log("Collision between %d and %d", a->parent->id, b->parent->id);
				a->HandleCollisionEvents(*b, true);
			}
			else
			{
				a->HandleCollisionEvents(*b, false);
			}
		}
	}

	if(needsCull)
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

void GameObjectList::PostRender(SDL_Renderer* renderer)
{
	for (GameObject* obj : objects)
		obj->PostRender(renderer);
}

void GameObjectList::CullPendingDeleteObjects()
{
	std::vector<GameObject*> tmpObjs;
	std::vector<Rigidbody*> tmpBodies;

	for (int i = 0; i < objects.size(); i++)
	{
		//If not pending delete, add to temp list
		if (!objects[i]->pendingDelete)
		{
			tmpObjs.push_back(objects[i]);

			if (objects[i]->components->rigidbody != nullptr)
			{
				tmpBodies.push_back(objects[i]->components->rigidbody);
			}
		}

		//Otherwise, call destructor: this will no longer exist
		else delete objects[i];
	}

	//Then swap the underlying values
	std::swap(this->objects, tmpObjs);
	std::swap(this->bodies, tmpBodies);
}
