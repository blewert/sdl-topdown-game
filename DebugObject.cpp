#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"

DebugObject::DebugObject(Scene* parentScene) : GameObject(parentScene)
{
	renderer = new DebugRenderer(this);
	timer = Random::Range(20, 100);


	SetPosition(Random::PositionInRect(0, 0, 800, 600));
}

DebugObject::~DebugObject()
{
	delete renderer;
}

void DebugObject::OnStart()
{
	GameObject::OnStart();
}

void DebugObject::Update()
{
	GameObject::Update();

	timer--;

	if (timer <= 0)
		this->Destroy();
}
