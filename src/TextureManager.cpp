#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

Texture* TextureManager::Get(const std::string& key)
{
	return textureMap.at(key);
}

Texture* TextureManager::operator[](const std::string& key)
{
	return Get(key);
}

Texture* TextureManager::Add(const std::string& key, const std::string& path, SDL_Renderer* renderer)
{
	//The key should not already exist
	SDL_assert(textureMap.find(key) == textureMap.end());

	//Load texture
	Texture* tex = new Texture(renderer, path);

	//The texture should be loaded
	SDL_assert(tex != nullptr);
	SDL_assert(tex->GetSDLTexture() != nullptr);

	//Add it to the map
	textureMap[key] = tex;

	return textureMap[key];
}

void TextureManager::Exit()
{
	SDL_Log("TextureManager::Exit");

	for (auto& tex : textureMap)
		delete tex.second;
}

TextureManager::~TextureManager()
{
	Exit();
}
