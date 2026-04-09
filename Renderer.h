#pragma once
#include "SDL.h"
#include "Component.h"
#include "Vector2.h"
#include <queue>

class GameObject;

struct DebugLine
{
	Vector2 start;
	Vector2 end;
	uint32_t color;

	DebugLine(Vector2 start, Vector2 end) : start(start), end(end), color(0xffffffff) { }

	DebugLine& WithColor(uint32_t color)
	{
		this->color = color;
		return *this;
	}

	//Assumes RGBA8888
	SDL_Color GetColor()
	{
		uint8_t r = (this->color >> 24) & 0xff;
		uint8_t g = (this->color >> 16) & 0xff;
		uint8_t b = (this->color >> 8) & 0xff;
		uint8_t a = (this->color >> 0) & 0xff;

		return SDL_Color{ r, g, b, a };
	}
};

class Renderer : public Component
{
public:
	Renderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect bounds);
	virtual ~Renderer();

	virtual void Render() = 0;
	
	virtual void PostRender()
	{
		for (auto& line : debugLines)
		{
			SDL_Color color = line.GetColor();
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawLine(renderer, line.start.x, line.start.y, line.end.x, line.end.y);
		}

		debugLines.clear();
	}

	virtual void Update();

	SDL_Rect GetBounds() { return bounds;  }

	void DrawLine(const Vector2& a, const Vector2& b, uint32_t color = 0xffffffff)
	{
		DebugLine line = DebugLine(a, b).WithColor(color);
		debugLines.push_back(line);
	}

protected:
	SDL_Rect bounds;
	SDL_Renderer* renderer;
	std::vector<DebugLine> debugLines;
};

