#include "MultipassRenderer.h"

MultipassRenderer::MultipassRenderer(GameObject* parentObj, const std::vector<Renderer*> renderers) 
	: Renderer(nullptr, parentObj, SDL_FRect{ 0, 0, 0, 0 })
{
	this->renderers = renderers;
}

MultipassRenderer::~MultipassRenderer()
{
	for (Renderer* renderer : renderers)
		delete renderer;
}

void MultipassRenderer::Add(Renderer* renderer)
{
	this->renderers.push_back(renderer);
}

void MultipassRenderer::Render()
{
	for (Renderer* renderer : renderers)
		renderer->Render();
}
