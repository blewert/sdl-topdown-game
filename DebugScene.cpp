#include "DebugScene.h"
#include "GameObject.h"
#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"

DebugScene::DebugScene()
{
	SDL_Log("DebugScene ctor");

	objects = new GameObjectList();

	for (int i = 0; i < 1000; i++)
	{
		objects->Add(new DebugObject(this));
	}
}

DebugScene::~DebugScene()
{
	this->Exit();
	SDL_Log("DebugScene dtor");
}

void DebugScene::OnStart()
{
	SDL_Log("DebugScene::OnStart");
	objects->OnStart();
}

void DebugScene::Update()
{

	if (Random::Value() > 0.9f)
	{
		for (int i = 0; i < 100; i++)
		{
			DebugObject* newObj = new DebugObject(this);
			objects->Add(newObj);
		}
	}

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

void DebugScene::Render(SDL_Renderer* renderer)
{
	objects->Render(renderer);
}
