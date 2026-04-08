#include "BoxCollider.h"
#include "Vector2.h"
#include "GameObject.h"
#include "Math.h"

void BoxCollider::Update()
{
}

SDL_Rect BoxCollider::GetWorldBounds()
{
	Vector2 pos = parent->GetPosition();
	return SDL_Rect{ (int)pos.x + localBounds.x, (int)pos.y + localBounds.y, localBounds.w, localBounds.h };
}

bool BoxCollider::CollidingWith(BoxCollider& other)
{
	SDL_Rect boundsA = this->GetWorldBounds();
	SDL_Rect boundsB = other.GetWorldBounds();

	return Collision::AABB(boundsA, boundsB);
}
