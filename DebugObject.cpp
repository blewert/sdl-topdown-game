#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"

DebugObject::DebugObject(Scene* parentScene) : GameObject(parentScene)
{
	timer = Random::Range(20, 100);
}

DebugObject::~DebugObject()
{
}

void DebugObject::OnStart()
{
}

void DebugObject::Update()
{
	timer--;

	if (timer <= 0)
		this->Destroy();
}
