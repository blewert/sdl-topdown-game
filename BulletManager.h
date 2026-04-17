#pragma once
#include "Scene.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include <vector>
#include <memory>

class BulletManager
{
public:
	BulletManager(Scene* parentScene, int capacity)
	{
		bulletPool = new ObjectPool<Bullet>(capacity);
		bulletPool->Allocate(capacity, Vector2(0, 0), Vector2(0, 0), parentScene);

		auto& data = bulletPool->GetData();

		for (int i = 0; i < capacity; i++)
		{
			if (!data[i].obj.has_value())
				continue;

			data[i].GetObj()->enabled = false;
		}

		activeBullets = new std::vector<PoolSlot<Bullet>*>();

		this->parentScene = parentScene;
	}

	~BulletManager()
	{
		delete bulletPool;
		delete activeBullets;
	}

	static void Initialise(Scene* parentScene, int capacity)
	{
		if (instance != nullptr)
			return;

		instance = new BulletManager(parentScene, capacity);
	}

	static void Render()
	{
		for (PoolSlot<Bullet>* bullet : *instance->activeBullets)
		{
			Bullet* obj = bullet->GetObj();

			if (!obj->IsAlive())
				continue;

			if (obj->pendingDelete)
				continue;

			obj->Render(instance->parentScene->GetRenderer());
		}
	}

	static void PostRender(SDL_Renderer* renderer)
	{
		for (PoolSlot<Bullet>* bullet : *instance->activeBullets)
		{
			Bullet* obj = bullet->GetObj();

			if (!obj->IsAlive())
				continue;

			if (obj->pendingDelete)
				continue;

			obj->PostRender(instance->parentScene->GetRenderer());
		}
	}

	static void Update()
	{
		bool bulletsNeedCull = false;

		////for(instance->bulletPool.)

		for (int i = 0; i < instance->activeBullets->size(); i++)
		{
			Bullet* obj = (*instance->activeBullets)[i]->GetObj();
			obj->Update();

			if (!obj->IsAlive())
			{
				SDL_Log("Cull rb for obj %d", obj->id);

				bulletsNeedCull = true;
				obj->enabled = false;
				obj->components->rigidbody->pendingDelete = true;

				(*instance->activeBullets)[i]->Reset(*instance->bulletPool);
			}
		}

		if (!bulletsNeedCull)
			return;

		std::vector<PoolSlot<Bullet>*> tmpBullets;

		for (PoolSlot<Bullet>* bulletSlot : *instance->activeBullets)
		{
			if (!bulletSlot->obj.has_value())
				continue;

			if (bulletSlot->GetObj()->IsAlive())
				tmpBullets.push_back(bulletSlot);
		}

		//SDL_Log("Releasing, there were %d bullets but now only %d", instance->activeBullets->size(), tmpBullets.size());
		
		std::swap(tmpBullets, *instance->activeBullets);
	}

	static void FireBullet(const Vector2& position, const Vector2& direction)
	{
		if (instance == nullptr)
			return;

		//Acquire a bullet, add to active list
		PoolSlot<Bullet>* bullet = instance->bulletPool->Acquire(position, direction, instance->parentScene);
		bullet->GetObj()->Reset(position, direction);
		instance->activeBullets->push_back(bullet);

		//SDL_Log("Add bullet, amount = %x", instance->activeBullets->size());
	}

	static void Exit()
	{
		if (instance == nullptr)
			return;
		
		delete instance;
	}

	static inline BulletManager& Instance()
	{
		return *instance;
	}

	static BulletManager* instance;

private:
	ObjectPool<Bullet>* bulletPool;
	Scene* parentScene;
	std::vector<PoolSlot<Bullet>*>* activeBullets;
};

