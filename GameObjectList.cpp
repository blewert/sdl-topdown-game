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
	bool rbsNeedCull = false;

	if (pendingAddObjects.size() > 0)
	{
		for (GameObject* obj : pendingAddObjects)
			objects.push_back(obj);

		pendingAddObjects.clear();
	}

	for (GameObject* obj : objects)
	{
		if (obj == nullptr)
			continue;

		if (!obj->enabled)
			continue;

		obj->Update();
		
		if (obj->pendingDelete)
			needsCull = true;
	}

	//SDL_Log("objects %d, bodies %d", objects.size(), bodies.size());

	//TODO: Spatial hashing here, this is 
	//      a bit intensive
	for (Rigidbody* a : bodies)
	{
		if (a->pendingDelete || a->parent->pendingDelete || a == nullptr)
		{
			rbsNeedCull = true;
			continue;
		}

		if (!a->parent->enabled)
			continue;

		for (Rigidbody* b : bodies)
		{
			if (!b->parent->enabled)
				continue;

			if (b->parent->pendingDelete || b->pendingDelete || b == nullptr)
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

	if (rbsNeedCull)
		CullPendingDeleteRBs();

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
	{
		if (!obj->enabled)
			continue;

		obj->Render(renderer);
	}
}

void GameObjectList::PostRender(SDL_Renderer* renderer)
{
	for (GameObject* obj : objects)
		obj->PostRender(renderer);
}

void GameObjectList::CullPendingDeleteRBs()
{
	std::vector<Rigidbody*> tmpBodies;

	for (int i = 0; i < bodies.size(); i++)
	{
		if (!bodies[i]->pendingDelete && !bodies[i]->parent->pendingDelete)
		{
			tmpBodies.push_back(bodies[i]);
		}
		else
		{
			if (bodies[i]->GetDeallocOnRemoval())
			{
				SDL_Log("Delete body %s", bodies[i]->parent->name.c_str());
				delete bodies[i];
				bodies[i] = nullptr;
			}
		}
	}

	std::swap(this->bodies, tmpBodies);
}

void GameObjectList::CullPendingDeleteObjects()
{
	std::vector<GameObject*> tmpObjs;
	
	for (int i = 0; i < objects.size(); i++)
	{
		//If not pending delete, add to temp list
		if (!objects[i]->pendingDelete)
		{
			tmpObjs.push_back(objects[i]);
		}

		//Otherwise, call destructor: this will no longer exist
		else
		{
			SDL_Log("Delete obj %s", objects[i]->name.c_str());
			delete objects[i];
			objects[i] = nullptr;
		}
	}

	//Then swap the underlying values
	std::swap(this->objects, tmpObjs);
}
