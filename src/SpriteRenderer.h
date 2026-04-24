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
	bool useOffset;
	int offset;

	SpriteAnimationParams& WithOffset(bool useOffset, int frameOffset)
	{
		this->useOffset = useOffset;
		this->offset = frameOffset;

		return *this;
	}

	SpriteAnimationParams& WithTexture(Texture* tex)
	{
		return WithDimensions(tex->GetDimensions());
	}

	SpriteAnimationParams& WithDimensions(SDL_Point dimensions)
	{
		this->frameW = dimensions.x;
		this->frameH = dimensions.y;

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

struct RenderMod
{
	SDL_Color col;
	bool activated;

	RenderMod& WithColor(uint8_t r, uint8_t g, uint8_t b)
	{
		this->col = SDL_Color{ r, g, b };
		return *this;
	}

	RenderMod& WithColor(const SDL_Color& color)
	{
		return WithColor(color.r, color.g, color.b);
	}

	RenderMod& WithColor(uint32_t color)
	{
		uint8_t r = (color >> 16) & 0xff;
		uint8_t g = (color >> 8)  & 0xff;
		uint8_t b = (color >> 0)  & 0xff;

		return WithColor(r, g, b);
	}

	RenderMod& WithActivated(bool status)
	{
		this->activated = status;
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

	SpriteRenderer(SDL_Renderer* renderer, GameObject* parent, SDL_FRect& bounds);

	//Setters
	void SetAnimated(bool animated, SpriteAnimationParams& params);
	void SetTexture(Texture* tex);
	void SetPivot(SpriteRendererPivot pivot) { this->pivot = pivot; }

	// Inherited via Renderer
	void Render() override;
	void Update() override;

	void SetAngle(float angleDegrees);
	void SetFlipped(bool flipX, bool flipY);
	void SetFlipX(bool flipX);
	void SetFlipY(bool flipY);

	void SetCustomRotatePivot(bool usePivot, SDL_Point pivot);

	float GetAngle() { return angleDegrees; }
	float GetFlipX() { return flipX; }
	float GetFlipY() { return flipY; }

	void SetRandomStartFrame()
	{
		if (!this->animated)
			return;

		int maxFrame = this->config.columns * this->config.rows;
		this->frameIdx = rand() % maxFrame;
	}

	void SetRenderMod(RenderMod renderMod);

protected:
	SDL_Texture* CreateBlankSDLTexFromExisting(SDL_Texture* tex);
	void NextFrame();
	SDL_Rect* GetSourceRect();

protected:
	RenderMod renderTexMod;

	bool useCustomRotatePivot = false;
	SDL_Point customRotatePivot;

	bool animated = false;
	SpriteAnimationParams config;
	Texture* tex;
	float frameTimer;
	float targetTime;
	int frameIdx = 0;

	SpriteRendererPivot pivot = SpriteRendererPivot::TopLeft;
	bool flipX = false;
	bool flipY = false;
	float angleDegrees = 0.0f;

	SDL_Rect srcRect;
};

