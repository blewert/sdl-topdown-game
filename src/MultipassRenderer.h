#pragma once
#include <vector>
#include "SDL.h"
#include "Renderer.h"

class MultipassRenderer : public Renderer
{
public:
	MultipassRenderer(GameObject* parentObj, const std::vector<Renderer*> renderers);
	~MultipassRenderer();

	void Add(Renderer* renderer);

protected:
	std::vector<Renderer*> renderers;

	// Inherited via Renderer
	virtual void Render() override;

	virtual void PostRender() override
	{
		for (Renderer* renderer : renderers)
		{
			renderer->PostRender();
		}
	}
};

