#pragma once
#include <vector>
#include "Vector2.h"
#include "Texture.h"
#include <map>
#include "Camera.h"

struct VFXCameraShake
{
	float intensity;
	float time;
	bool active;
};

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
	float scale;
	VFXTexData texData;

	bool isLine = false;
	Vector2 endPos = Vector2(0, 0);
	uint32_t lineColor = 0xffffffff;
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

	static void CameraShake(float time, float intensity);

	static void LoadEffect(Texture* tex, const std::string& effectKey, int cols, int rows, const Vector2& frameSize);
	static void SpawnEffect(const Vector2& position, const std::string& key, float fps=8, float scale = 1.0f, float angle=0.0f, bool loop=false, float timeLeft=-1.0f);

	static void DrawLine(const Vector2& startPos, const Vector2& endPos, const uint32_t lineColor, float time);

private:
	std::map<std::string, VFXTexData> effectTexMap;
	static VFXManager* GetInstance();
	static VFXManager* instance;
	Camera* camera = nullptr;

	VFXCameraShake currentShakeParams;
};

