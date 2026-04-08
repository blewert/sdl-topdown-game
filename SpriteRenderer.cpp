#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Scene.h"

SpriteRenderer::SpriteRenderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect& bounds) : Renderer(renderer, parent, bounds)
{
	tex = nullptr;
	config = SpriteAnimationParams();
	frameTimer = 0;
	targetTime = 0;
}

void SpriteRenderer::SetAnimated(bool animated, SpriteAnimationParams& params)
{
	this->animated = animated;
	this->config = params;

	targetTime = 1.0f / (float)params.fps;
}

void SpriteRenderer::SetTexture(Texture* tex)
{
	this->tex = tex;
}

void SpriteRenderer::Render()
{
	if (animated)
	{
		frameTimer += Time::deltaTime;

		if (frameTimer >= targetTime)
		{
			frameTimer = Time::deltaTime;
			NextFrame();
		}
	}

	//if (parent->id == 5)
	//{
	//	SDL_Log("%f targetTime, %f timer, %d idx", targetTime, frameTimer, frameIdx);
	//}

	if (tex == nullptr)
		return;

	Camera* camera = parent->parentScene->GetCamera();
	SDL_Rect spriteBounds = camera->CalculateBounds(bounds);

	if (pivot == SpriteRendererPivot::Center)
	{
		spriteBounds.x -= spriteBounds.w / 2;
		spriteBounds.y -= spriteBounds.h / 2;
	}

	SDL_RenderCopy(renderer, tex->GetSDLTexture(), GetSourceRect(), &spriteBounds);
}

void SpriteRenderer::Update()
{
	Renderer::Update();

	this->bounds.w = config.frameW;
	this->bounds.h = config.frameH;
}

void SpriteRenderer::NextFrame()
{
	frameIdx++;

	if (frameIdx >= (this->config.columns * this->config.rows))
		frameIdx = 0;

	int w = this->config.frameW;
	int h = this->config.frameH;

	int x = frameIdx % this->config.columns;
	int y = frameIdx / this->config.columns;

	//if (parent->id == 5)
	//{
	//	SDL_Log("%d, %d :: %d, %d -- %d %d %d %d", w, h, x, y, x*w, y*h, w, h);
	//}

	srcRect = SDL_Rect{ x*w, y*h, w, h };
}

SDL_Rect* SpriteRenderer::GetSourceRect()
{
	return (this->animated) ? &srcRect : NULL;
}
