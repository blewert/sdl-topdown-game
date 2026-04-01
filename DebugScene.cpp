#include "DebugScene.h"
#include "GameObject.h"
#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"

DebugScene::DebugScene()
{
	SDL_Log("DebugScene ctor");

	for (int i = 0; i < 100000; i++)
	{
		objects.Add(new DebugObject(this));
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
}

void DebugScene::Update()
{
	objects.Update();
	SDL_Log("There are %d objects", objects.Count());

	if (Random::Value() > 0.9f)
	{
		for (int i = 0; i < 10; i++)
		{
			DebugObject* newObj = new DebugObject(this);
			newObj->SetPosition(Random::PositionInRect(0, 0, 800, 600));
			objects.Add(newObj);
		}
	}

}

void DebugScene::OnEnd()
{
	SDL_Log("DebugScene::OnEnd");
}

void DebugScene::Exit()
{
	SDL_Log("DebugScene::Exit");
}
