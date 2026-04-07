#include "DebugScene.h"
#include "GameObject.h"
#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"
#include "TextureManager.h"

DebugScene::DebugScene(SDL_Renderer* renderer) : Scene(renderer)
{
	SDL_Log("DebugScene ctor");

	objects = new GameObjectList();
}

DebugScene::~DebugScene()
{
	this->Exit();
}

void DebugScene::OnStart()
{
	SDL_Log("DebugScene::OnStart");
	objects->OnStart();
}

void DebugScene::Update()
{
	objects->Update();
}

void DebugScene::OnEnd()
{
	SDL_Log("DebugScene::OnEnd");
	objects->OnEnd();
}

void DebugScene::Exit()
{
	SDL_Log("DebugScene::Exit");
}

void DebugScene::Render()
{
	objects->Render(renderer);
}
