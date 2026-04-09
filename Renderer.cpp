#include "Renderer.h"
#include "Component.h"
#include "GameObject.h"
#include "Scene.h"

Renderer::Renderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect bounds)
	: Component(parent), bounds(bounds), renderer(renderer)
{
}

Renderer::~Renderer()
{

}

void Renderer::PostRender()
{
	for (auto& line : debugLines)
	{
		Camera* cam = parent->parentScene->GetCamera();
		line.start = cam->WorldToScreenPos(line.start);
		line.end = cam->WorldToScreenPos(line.end);

		SDL_Color color = line.GetColor();
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(renderer, line.start.x, line.start.y, line.end.x, line.end.y);
	}

	debugLines.clear();
}

void Renderer::Update()
{
	Vector2 pos = this->parent->GetPosition();
	this->bounds = pos.ToRenderRect(this->bounds.w, this->bounds.h);
}
