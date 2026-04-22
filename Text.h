#pragma once
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Vector2.h"

enum class TextAlign
{
	Start,
	Center,
	End
};

class Text
{
public:
	Text(SDL_Renderer* renderer, const std::string& text, const std::string& fontString);
	~Text();

	void SetAlign(TextAlign horizontalAlign = TextAlign::Start, TextAlign verticalAlign = TextAlign::Start);
	void Render();
	void SetPosition(const Vector2& position);
	Vector2 GetPosition();

	void SetFont(const std::string& fontString);
	void SetText(const std::string& text);
	void SetColor(const SDL_Color& color);

	static void LoadFont(const std::string& fontStringKey, const std::string& path, int pointSize);
	static void Exit();

private:
	SDL_Texture* fontTexture = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* fontObj = nullptr;

	std::string text;

	SDL_Rect fontBBox;
	SDL_Color color;
	Vector2 position;

	TextAlign horizontalAlign;
	TextAlign verticalAlign;

	void CreateTexture(const std::string& text);
	static void TryInitialise();

	static bool hasInit;
	static std::map<std::string, TTF_Font*> fontMap;
};

