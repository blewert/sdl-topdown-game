#pragma once
#include "SDL.h"
#include "Component.h"
#include "Vector2.h"
#include <queue>

class GameObject;

class Renderer : public Component
{
public:
	Renderer(SDL_Renderer* renderer, GameObject* parent, SDL_Rect bounds);
	virtual ~Renderer();

	virtual void Render() = 0;
	
	virtual void PostRender()
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_Log("Count %d", debugLines.size());

		for (auto& line : debugLines)
		{
			SDL_Log("Draw line %s to %s", line.first.ToString().c_str(), line.second.ToString().c_str());
			SDL_RenderDrawLine(renderer, line.first.x, line.first.y, line.second.x, line.second.y);
		}

		debugLines.clear();
	}

	virtual void Update();

	SDL_Rect GetBounds() { return bounds;  }

	void DrawLine(const Vector2& a, const Vector2& b)
	{
		debugLines.push_back(std::pair<Vector2, Vector2>(a, b));
		SDL_Log("Add line %d", debugLines.size());
	}

protected:
	SDL_Rect bounds;
	SDL_Renderer* renderer;
	std::vector<std::pair<Vector2, Vector2>> debugLines;
};

