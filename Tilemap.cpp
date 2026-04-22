#include "Tilemap.h"

Tilemap::Tilemap(Scene* parentScene, SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->parentScene = parentScene;
}

Tilemap::~Tilemap()
{
}

void Tilemap::SetTileSize(float tilePixelSize)
{
	this->tilePixelSize = tilePixelSize;
}

void Tilemap::SetMapSize(int width, int height)
{
	this->mapWidth = width;
	this->mapHeight = height;
}

void Tilemap::Initialise()
{
	if (hasInited)
		return;

	hasInited = true;

	AddLayer();
}

SDL_Point Tilemap::Convert1DTo2DCoord(int id, int cols, int rows)
{
	int x = id % cols;
	int y = id / cols;

	return SDL_Point{ x, y };
}

TilemapLayer& Tilemap::AddLayer()
{
	layers.push_back(TilemapLayer(mapWidth, mapHeight));
	return layers.back();
}

void Tilemap::Update()
{
}

void Tilemap::Render()
{
	Camera* cam = parentScene->GetCamera();
	Vector2 camPos = cam->GetPosition();
	float pixelScale = cam->GetPixelScale();

	Vector2 playerPos = playerObject->GetPosition();
	playerPos -= position;
	playerPos /= (tilePixelSize / pixelScale) * scale;

	SDL_Point playerGridPos { floorf(playerPos.x), floorf(playerPos.y) };
	
	static int kernelSize = 8;

	SDL_Point start;
	start.x = SDL_clamp(playerGridPos.x - kernelSize, 0, mapWidth - 1);
	start.y = SDL_clamp(playerGridPos.y - kernelSize, 0, mapHeight - 1);

	SDL_Point end;
	end.x = SDL_clamp(playerGridPos.x + kernelSize, 0, mapWidth - 1);
	end.y = SDL_clamp(playerGridPos.y + kernelSize, 0, mapHeight - 1);

	SDL_Point diff = { start.x - end.x, start.y - end.y };
	
	if (diff.x == 0 && diff.y == 0)
		return;

	for (TilemapLayer& layer : layers)
	{
		for (int y = start.y; y < end.y; y++)
		{
			auto& row = layer.tileData[y];

			for (int x = start.x; x < end.x; x++)
			{
				Tile& cell = row[x];

				if (cell.id < 0)
					continue;

				SDL_Point gridPos = Convert1DTo2DCoord(cell.id, tilemapGridSize.x, tilemapGridSize.y);

				float xOffsetInTilemap = gridPos.x * tilePixelSize;
				float yOffsetInTilemap = gridPos.y * tilePixelSize;

				float xOffsetInWorld = x * (tilePixelSize * scale);
				float yOffsetInWorld = y * (tilePixelSize * scale);

				SDL_Rect srcRect = { xOffsetInTilemap, yOffsetInTilemap, tilePixelSize, tilePixelSize };
				SDL_FRect destRect = { position.x + xOffsetInWorld, position.y + yOffsetInWorld, tilePixelSize * scale, tilePixelSize * scale };

				destRect.x -= camPos.x * pixelScale;
				destRect.y -= camPos.y * pixelScale;

				SDL_RenderCopyF(renderer, tilemapTex->GetSDLTexture(), &srcRect, &destRect);
			}
		}
	}
}

void Tilemap::SetPosition(const Vector2& position)
{
	this->position = position;
}

void Tilemap::SetTexture(Texture* texture, int cols, int rows)
{
	this->tilemapTex = texture;
	tilemapGridSize.x = cols;
	tilemapGridSize.y = rows;
}
