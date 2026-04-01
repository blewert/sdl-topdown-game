#include "DebugScene.h"
#include "GameObject.h"
#include "SDL.h"

DebugScene::DebugScene()
{
	SDL_Log("DebugScene ctor");

	objects = new std::vector<GameObject>();
}

DebugScene::~DebugScene()
{
	SDL_Log("DebugScene dtor");

	delete[] objects;
}

void DebugScene::OnStart()
{
	SDL_Log("DebugScene::OnStart");
}

void DebugScene::Update()
{
	SDL_Log("DebugScene::Update");
}

void DebugScene::OnEnd()
{
	SDL_Log("DebugScene::OnEnd");
}

void DebugScene::Exit()
{
	SDL_Log("DebugScene::Exit");
}
