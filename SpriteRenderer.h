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

	SpriteAnimationParams& WithTexture(Texture* tex)
	{
		return WithDimensions(tex->GetDimensions());
	}

	SpriteAnimationParams& WithDimensions(SDL_Point dimensions)
	{
		this->frameH = dimensions.x;
		this->frameW = dimensions.y;

		return *this;
	}

	SpriteAnimationParams& WithRowCols(int rows, int cols)
	{
		this->rows = rows;
		this->columns = cols;

		return *this;
	}

	SpriteAnimationParams& WithFPS(int fps)
	{
		this->fps = fps;
		return *this;
	}
};

enum class SpriteRendererPivot
{
	TopLeft,
	Center
};

class SpriteRenderer : public Renderer
{
public:

	SpriteRenderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect& bounds);

	//Setters
	void SetAnimated(bool animated, SpriteAnimationParams& params);
	void SetTexture(Texture* tex);
	void SetPivot(SpriteRendererPivot pivot) { this->pivot = pivot; }

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

	SpriteRendererPivot pivot = SpriteRendererPivot::TopLeft;

	

	SDL_Rect srcRect;
};

