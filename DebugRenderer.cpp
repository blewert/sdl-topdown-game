#include "DebugRenderer.h"
#include "GameObject.h"
#include "Scene.h"

void DebugRenderer::Render()
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(renderer, &bounds);
}
