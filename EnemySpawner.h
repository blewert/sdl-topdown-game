#pragma once
#include "Timer.h"
#include "json.hpp"
#include <fstream>
#include <vector>

class Scene;

class EnemySpawner
{
public:
	EnemySpawner(const std::string& spawnPointsFile, Scene* scene);
	void Update();

private:
	Timer spawnTimer;
	Scene* parent;
	std::vector<SDL_FPoint> spawnPoints;

	void LoadSpawnpointsFromDisk(const std::string& spawnPointsFile);
};

