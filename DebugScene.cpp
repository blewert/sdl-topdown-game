#include "DebugScene.h"
#include "SDL.h"

DebugScene::DebugScene()
{
	SDL_Log("DebugScene ctor");
}

DebugScene::~DebugScene()
{
	SDL_Log("DebugScene dtor");
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
