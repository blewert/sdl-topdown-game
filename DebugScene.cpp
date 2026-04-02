#include "DebugScene.h"
#include "GameObject.h"
#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"
#include "TextureManager.h"

DebugScene::DebugScene(SDL_Renderer* renderer) : Scene(renderer)
{
	tex = TextureManager::Instance().Get("test-tex");

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

	for (int i = 0; i < 1500; i++)
	{
		DebugObject* newObj = new DebugObject(this);
		objects->Add(newObj);
	}
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
	delete tex;
}

void DebugScene::Render()
{
	objects->Render(renderer);
	tex->Render(Vector2(10, 10));
}
