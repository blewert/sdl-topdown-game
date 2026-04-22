#pragma once
#include "SDL.h"
#include "Scene.h"
#include "Text.h"

class GameOverScene : public Scene
{
public:
	GameOverScene(SDL_Renderer* renderer);
	~GameOverScene();


	// Inherited via Scene
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnd() override;
	virtual void Exit() override;

private:
	Text* titleText;

};

