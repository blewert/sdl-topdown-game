#pragma once
#include <vector>
#include "Vector2.h"
#include "Texture.h"
#include <map>
#include "Camera.h"

struct VFXTexData
{
	Texture* tex;
	int rows;
	int cols;
	int frameSizeX;
	int frameSizeY;
};

struct VFXInstance
{
	Vector2 position;
	float angleDegrees;
	float timeLeft;
	bool loop;
	bool enabled;
	int frameIdx;
	float timer;
	float fps;
	VFXTexData texData;
};

class VFXManager
{
public:
	~VFXManager();
	std::vector<VFXInstance>* instancePool;
	static VFXManager* Initialise();
	static void SetCamera(Camera* camera);
	static void Update();
	static void Render(SDL_Renderer* renderer);

	static void LoadEffect(Texture* tex, const std::string& effectKey, int cols, int rows, const Vector2& frameSize);
	static void SpawnEffect(const Vector2& position, const std::string& key, float fps=8, float angle=0.0f, bool loop=false, float timeLeft=-1.0f);

private:
	std::map<std::string, VFXTexData> effectTexMap;
	static VFXManager* GetInstance();
	static VFXManager* instance;
	Camera* camera = nullptr;
};

