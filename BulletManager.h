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
		bulletPool = new ObjectPool<Bullet>(1000);
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
				bulletsNeedCull = true;
				obj->Destroy();
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

		SDL_Log("Releasing, there were %d bullets but now only %d", instance->activeBullets->size(), tmpBullets.size());
		
		std::swap(tmpBullets, *instance->activeBullets);
	}

	static void FireBullet(const Vector2& position, const Vector2& direction)
	{
		if (instance == nullptr)
			return;

		//Acquire a bullet, add to active list
		PoolSlot<Bullet>* bullet = instance->bulletPool->Acquire(position, direction, instance->parentScene);
		instance->activeBullets->push_back(bullet);

		SDL_Log("Add bullet, amount = %x", instance->activeBullets->size());
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

