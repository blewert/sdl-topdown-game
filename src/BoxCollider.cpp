#include "BoxCollider.h"
#include "Vector2.h"
#include "GameObject.h"
#include "Math.h"
#include "Camera.h"
#include "Scene.h"

void BoxCollider::Update()
{
}

SDL_FRect BoxCollider::GetWorldBoundsF()
{
	Vector2 pos = parent->GetPosition();
	return SDL_FRect{ pos.x + localBounds.x, pos.y + localBounds.y, (float)localBounds.w, (float)localBounds.h };
}

SDL_Rect BoxCollider::GetWorldBounds()
{
	Vector2 pos = parent->GetPosition();
	pos *= parent->parentScene->GetCamera()->GetPixelScale();
		
	//parent->parentScene->GetCamera()->WorldToScreenPos(pos);

	return SDL_Rect{ int(pos.x + localBounds.x), int(pos.y + localBounds.y), (int)localBounds.w, (int)localBounds.h };
}

bool BoxCollider::CollidingWith(BoxCollider& other)
{
	SDL_Rect boundsA = this->GetWorldBounds();
	SDL_Rect boundsB = other.GetWorldBounds();

	return Collision::AABB(boundsA, boundsB);
}
