#include "Text.h"

bool Text::hasInit = false;
std::map<std::string, TTF_Font*> Text::fontMap;

Text::Text(SDL_Renderer* renderer, const std::string& text, const std::string& fontString)
{
    TryInitialise();

    this->color = { 0xff, 0xff, 0xff, 0xff };
    this->fontBBox = SDL_Rect{ 0, 0, 0, 0 };
    this->renderer = renderer;

    SetAlign(TextAlign::Start, TextAlign::Start);
    SetFont(fontString);
    SetText(text);
}

Text::~Text()
{
    delete fontTexture;
}

void Text::SetAlign(TextAlign horizontalAlign, TextAlign verticalAlign)
{
    this->horizontalAlign = horizontalAlign;
    this->verticalAlign = verticalAlign;
}

void Text::Render()
{
    SDL_assert(fontTexture != nullptr);
    SDL_assert(fontObj != nullptr);

    SDL_FRect renderBox = { position.x, position.y, fontBBox.w, fontBBox.h };

    //Horizontal alignment
    if (horizontalAlign == TextAlign::Center)
        renderBox.x -= fontBBox.w / 2.0f;

    else if (horizontalAlign == TextAlign::End)
        renderBox.x -= fontBBox.w;
    //---

    //Vertical alignment
    if (verticalAlign == TextAlign::Center)
        renderBox.y -= fontBBox.h / 2.0f;

    else if (verticalAlign == TextAlign::End)
        renderBox.y -= fontBBox.h;
    //---

    SDL_RenderCopyF(renderer, fontTexture, NULL, &renderBox);
}

void Text::SetPosition(const Vector2& position)
{
    this->position = position;
}

Vector2 Text::GetPosition()
{
    return position;
}

void Text::SetFont(const std::string& fontString)
{
    //Does the key exist? If not, die
    SDL_assert(fontMap.count(fontString) > 0);

    //Otherwise set the font
    this->fontObj = fontMap[fontString];
}

void Text::SetText(const std::string& text)
{
    CreateTexture(text);
}

void Text::SetColor(const SDL_Color& color)
{
    this->color = color;
}

void Text::LoadFont(const std::string& fontStringKey, const std::string& path, int pointSize)
{
    TryInitialise();

    TTF_Font* loadedFont = TTF_OpenFont(path.c_str(), pointSize);
    SDL_assert(loadedFont != NULL);

    fontMap[fontStringKey] = loadedFont;
}

void Text::Exit()
{
    for (auto& keyVal : fontMap)
    {
        TTF_Font* font = keyVal.second;
        TTF_CloseFont(font);
    }

    fontMap.clear();
}

void Text::CreateTexture(const std::string& text)
{
    if (fontTexture != nullptr)
    {
        SDL_DestroyTexture(fontTexture);
        fontTexture = nullptr;
    }

    //Create texture
    SDL_Surface* surf = TTF_RenderText_Blended(fontObj, text.c_str(), color);
    fontTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    //Create size box
    int w, h;
    TTF_SizeText(fontObj, text.c_str(), &w, &h);
    this->fontBBox = { 0, 0, w, h };
}

void Text::TryInitialise()
{
    if (hasInit)
        return;

    TTF_Init();
    hasInit = true;
}
