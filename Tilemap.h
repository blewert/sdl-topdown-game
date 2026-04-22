#pragma once
#include "Scene.h"
#include "Texture.h"

struct Tile
{
	int x, y;
	int id;

	Tile(int id, int x, int y) : id(id), x(x), y(y)
	{

	}
};

struct TilemapLayer
{
	std::vector<std::vector<Tile>> tileData;

	TilemapLayer(int width, int height)
	{
		tileData.reserve(width * height);

		for (int y = 0; y < height; y++)
		{
			std::vector<Tile> innerLayer;

			for (int x = 0; x < width; x++)
				innerLayer.push_back(Tile(rand() % 101 + 1, x, y));

			tileData.push_back(innerLayer);
		}
	}
};

class Tilemap
{
public:
	Tilemap(Scene* parentScene, SDL_Renderer* renderer);
	~Tilemap();

	void SetPosition(const Vector2& position);
	void SetTexture(Texture* texture, int cols, int rows);
	void SetTileSize(float tilePixelSize);
	void SetMapSize(int width, int height);
	void SetScale(float scale) { this->scale = scale; }
	void SetPlayerObject(GameObject* object) { playerObject = object;  }
	void Initialise();

	static SDL_Point Convert1DTo2DCoord(int id, int cols, int rows);

	TilemapLayer& AddLayer();

	void Update();
	void Render();

private:
	Texture* tilemapTex = nullptr;
	SDL_Point tilemapGridSize;

	Scene* parentScene = nullptr;
	SDL_Renderer* renderer = nullptr;
	Vector2 position = Vector2::zero;

	float tilePixelSize = 0.0f;
	float scale = 1.0f;
	int mapWidth = 0, mapHeight = 0;

	bool hasInited;

	std::vector<TilemapLayer> layers;
	GameObject* playerObject;
};

