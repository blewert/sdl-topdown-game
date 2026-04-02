#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Time.h"

struct SpriteAnimationParams
{
	int frameW;
	int frameH;
	int rows;
	int columns;
	int fps;
};

class SpriteRenderer : public Renderer
{
public:

	SpriteRenderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect& bounds);
	void SetAnimated(bool animated, SpriteAnimationParams& params);
	void SetTexture(Texture* tex);

	// Inherited via Renderer
	void Render() override;
	void Update() override;

protected:
	void NextFrame();
	SDL_Rect* GetSourceRect();

protected:
	bool animated = false;
	SpriteAnimationParams config;
	Texture* tex;
	float frameTimer;
	float targetTime;
	int frameIdx = 0;

	SDL_Rect srcRect;
};

