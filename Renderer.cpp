#include "Renderer.h"
#include "Component.h"
#include "GameObject.h"

Renderer::Renderer(GameObject* parent, SDL_Rect bounds) : Component(parent), bounds(bounds) {}
void Renderer::Update()
{
	Vector2 pos = this->parent->GetPosition();
	this->bounds = pos.ToRenderRect(this->bounds.w, this->bounds.h);
}
