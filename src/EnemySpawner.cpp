#include "EnemySpawner.h"
#include "Math.h"
#include "EnemyObject.h"
#include "Scene.h"

EnemySpawner::EnemySpawner(const std::string& spawnPointsFile, Scene* scene, int spawnCap) : parent(scene), spawnCap(spawnCap)
{
	LoadSpawnpointsFromDisk(spawnPointsFile);
	spawnTimer = Timer(1.0f);
}

void EnemySpawner::Update()
{
	// Add code to spawn enemies over time here.
}

void EnemySpawner::LoadSpawnpointsFromDisk(const std::string& spawnPointsFile)
{
	std::ifstream inputFile(spawnPointsFile);
	SDL_assert(inputFile.is_open());

	using nlohmann::json;
	json jsonObj = json::parse(inputFile);

	int id = 0;

	for (json& point : jsonObj)
	{
		float x = point["x"];
		float y = point["y"];

		spawnPoints.push_back({ x, y });
	}
}
