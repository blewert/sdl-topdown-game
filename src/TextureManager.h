#pragma once
#include "Texture.h"
#include <map>

class TextureManager
{
public:
	static inline TextureManager& Instance()
	{
		if (instance == nullptr)
			instance = new TextureManager();

		return *instance;
	}

	Texture* Get(const std::string& key);
	Texture* operator[](const std::string& key);
	Texture* Add(const std::string& key, const std::string& path, SDL_Renderer* renderer);

	void Exit();
	~TextureManager();

protected:
	static TextureManager* instance;
	std::map<std::string, Texture*> textureMap;
};
