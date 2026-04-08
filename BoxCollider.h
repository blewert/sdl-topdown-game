#pragma once
#include "SDL.h"
#include "Component.h"

class BoxCollider : public Component
{

public:
	virtual void Update() override;

	BoxCollider(GameObject* parent, SDL_Rect localBounds) : Component(parent), localBounds(localBounds)
	{
	}

	SDL_Rect GetWorldBounds();
	bool CollidingWith(BoxCollider& other);

private:
	SDL_Rect localBounds;
};

