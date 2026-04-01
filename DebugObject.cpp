#include "DebugObject.h"
#include "SDL.h"
#include "Math.h"

DebugObject::DebugObject(Scene* parentScene) : GameObject(parentScene)
{
	renderer = new DebugRenderer(this);
	//components = new ComponentList();

	//components->Add(renderer);

	timer = Random::Range(20, 100);
}

DebugObject::~DebugObject()
{
	delete renderer;
}

void DebugObject::OnStart()
{
}

void DebugObject::Update()
{
	//components->Update();

	timer--;

	if (timer <= 0)
		this->Destroy();
}
