#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Scene.h"

SpriteRenderer::SpriteRenderer(SDL_Renderer* renderer, GameObject* parent, SDL_FRect& bounds) : Renderer(renderer, parent, bounds)
{
	renderTexMod = RenderMod().WithColor(0).WithActivated(false);
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

SDL_Texture* SpriteRenderer::CreateBlankSDLTexFromExisting(SDL_Texture* tex)
{
	int w, h;
	unsigned int format;

	SDL_Texture* sdlTex = tex;
	SDL_QueryTexture(sdlTex, &format, NULL, &w, &h);

	return SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
}

void SpriteRenderer::Render()
{
	if (!enabled)
		return;

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
	SDL_FRect spriteBounds = camera->CalculateBounds(bounds);

	//Within SDL_render.c (ln ~3705), flip modes are used as
	//flags, despite this being an enum type
	uint32_t uflipFlags = flipX | (flipY << 1);
	SDL_RendererFlip flipFlags = (SDL_RendererFlip)uflipFlags;

	SDL_Point* pivotRct = (useCustomRotatePivot) ? &customRotatePivot : NULL;

	if (pivot == SpriteRendererPivot::Center)
	{
		spriteBounds.x -= spriteBounds.w / 2;
		spriteBounds.y -= spriteBounds.h / 2;
	}

	if (renderTexMod.activated)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

		//Create target texture from this
		SDL_Texture* spriteTex = tex->GetSDLTexture();
		SDL_Texture* targetTex = CreateBlankSDLTexFromExisting(spriteTex);
		SDL_Color col = renderTexMod.col;

		//Draw red
		SDL_SetRenderTarget(renderer, targetTex);
		SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 0);
		SDL_RenderClear(renderer);

		//This blend function masks such that the sprite alpha is used
		//but the colour of targetTex is used.
		SDL_BlendMode blendMode = SDL_ComposeCustomBlendMode(
			SDL_BLENDFACTOR_DST_COLOR,
			SDL_BLENDFACTOR_SRC_COLOR,
			SDL_BLENDOPERATION_ADD,
			SDL_BLENDFACTOR_ZERO,
			SDL_BLENDFACTOR_DST_ALPHA,
			SDL_BLENDOPERATION_ADD
		);

		blendMode = SDL_BLENDMODE_ADD;

		//Copy existing tex using this blend func
		SDL_SetTextureBlendMode(targetTex, blendMode);
		SDL_RenderCopy(renderer, spriteTex, NULL, NULL);

		//Reset renderer to screen, Render the masked sprite
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopyExF(renderer, targetTex, GetSourceRect(), &spriteBounds, angleDegrees, NULL, flipFlags);

		//Reset blend mode & get rid of scratch texture
		SDL_SetTextureBlendMode(spriteTex, SDL_BLENDMODE_BLEND);
		SDL_DestroyTexture(targetTex);
	}
	else
	{
		//Otherwise, just render normally. Note there is no need to check angle or
		//flip and whether to call RenderCopy instead, as this is what RenderCopyEx
		//does under the hood anyways.
		SDL_RenderCopyExF(renderer, tex->GetSDLTexture(), GetSourceRect(), &spriteBounds, angleDegrees, NULL, (SDL_RendererFlip)flipFlags);


		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//SDL_RenderDrawRect(renderer, &spriteBounds);

		//SDL_Rect rct = { spriteBounds.x - 2, spriteBounds.y - 2, 4, 4 };
		//SDL_RenderFillRect(renderer, &rct);
	}
}

void SpriteRenderer::Update()
{
	if (!enabled)
		return;

	Renderer::Update();

	if (this->bounds.w <= 0 || this->bounds.h <= 0)
	{
		this->bounds.w = config.frameW;
		this->bounds.h = config.frameH;
	}
}

void SpriteRenderer::SetAngle(float angleDegrees)
{
	this->angleDegrees = angleDegrees;
}

void SpriteRenderer::SetFlipped(bool flipX, bool flipY)
{
	SetFlipX(flipX);
	SetFlipY(flipY);
}

void SpriteRenderer::SetFlipX(bool flipX)
{
	this->flipX = flipX;
}

void SpriteRenderer::SetFlipY(bool flipY)
{
	this->flipY = flipY;
}

void SpriteRenderer::SetRenderMod(RenderMod renderMod)
{
	this->renderTexMod = renderMod;
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
	if (!this->animated && !this->config.useOffset)
		return NULL;

	else if (this->config.useOffset)
	{
		int w = this->config.frameW;
		int h = this->config.frameH;

		int x = this->config.offset % this->config.columns;
		int y = this->config.offset / this->config.columns;

		SDL_Rect rct{ x * w, y * h, w, h };
		srcRect = rct;
	}

	return &srcRect;
}

void SpriteRenderer::SetCustomRotatePivot(bool usePivot, SDL_Point pivot)
{
	this->useCustomRotatePivot = usePivot;
	this->customRotatePivot = pivot;
}
