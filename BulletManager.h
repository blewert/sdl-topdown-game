#pragma once
#include "Scene.h"
#include "ObjectPool.h"
#include "Bullet.h"

class BulletManager
{
public:
	BulletManager(Scene* parentScene, int capacity);
	~BulletManager();

	static void Initialise(Scene* parentScene, int capacity)
	{
		if (instance != nullptr)
			return;

		instance = new BulletManager(parentScene, capacity);
	}

	static void FireBullet(const Vector2& position, const Vector2& direction)
	{
		if (instance == nullptr)
			return;

		PoolSlot<Bullet>* bullet = instance->bulletPool->Acquire(position, direction, instance->parentScene);

		SDL_Log("Bullet %d", bullet->GetObj());
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
};

