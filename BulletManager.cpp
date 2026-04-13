#include "BulletManager.h"

BulletManager* BulletManager::instance = nullptr;

BulletManager::BulletManager(Scene* parentScene, int capacity)
{
	bulletPool = new ObjectPool<Bullet>(1000);
	this->parentScene = parentScene;
}

BulletManager::~BulletManager()
{
	delete bulletPool;
}
