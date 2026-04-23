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
}

void Tilemap::LoadFromDisk(const std::string& path)
{
	using namespace nlohmann;

	std::ifstream jsonFile(path);
	SDL_assert(jsonFile.is_open());

	json jsonObj = json::parse(jsonFile);
	jsonFile.close();

	//----

	int tileSize = jsonObj["tileSize"];
	int mapWidth = jsonObj["mapWidth"] + 2;
	int mapHeight = jsonObj["mapHeight"] + 2;

	this->tilePixelSize = tileSize;
	this->mapHeight = mapHeight;
	this->mapWidth = mapWidth;

	Initialise();

	std::vector<json> layers = jsonObj["layers"];

	for (json& layer : layers)
	{
		std::string name = layer["name"];
		std::vector<json> tiles = layer["tiles"];

		TilemapLayer& layer = AddLayer();

		layer.name = name;
		layer.collision = (name == "Collision");

		for (json& tile : tiles)
		{
			std::string idStr = tile["id"];
			int id = std::stoi(idStr);
			int x = tile["x"];
			int y = tile["y"];

			layer.tileData[y][x] = Tile(id, x, y);
		}
	}
	
	std::reverse(this->layers.begin(), this->layers.end());
}

void Tilemap::GetStreamingCoordsForObject(const SDL_Point& kernel, GameObject* obj, SDL_Point* start, SDL_Point* end)
{
	//Get camera properties for conversion to cam space
	Camera* cam = parentScene->GetCamera();
	Vector2 camPos = cam->GetPosition();
	float pixelScale = cam->GetPixelScale();

	//Find the object's position with respect to the grid of
	//this tilemap
	Vector2 objPos = obj->GetPosition();
	objPos -= position;
	objPos /= (tilePixelSize / pixelScale) * scale;

	//Floor position to get true grid position
	SDL_Point objGridPos{ floorf(objPos.x), floorf(objPos.y) };

	//Find lower bound (clamp x & y to valid ranges)
	start->x = SDL_clamp(objGridPos.x - kernel.x, 0, mapWidth - 1);
	start->y = SDL_clamp(objGridPos.y - kernel.y, 0, mapHeight - 1);

	//Find upper bound (clamp x & y to valid ranges)
	end->x = SDL_clamp(objGridPos.x + kernel.x, 0, mapWidth - 1);
	end->y = SDL_clamp(objGridPos.y + kernel.y, 0, mapHeight - 1);
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

	SDL_Point start, end;
	GetStreamingCoordsForObject({ 10, 7 }, playerObject, &start, &end);

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

				//This fixes screen tearing issues
				SDL_Rect destRectI = { SDL_floor(destRect.x), SDL_floor(destRect.y), SDL_floor(destRect.w), SDL_floor(destRect.h) };

				SDL_RenderCopy(renderer, tilemapTex->GetSDLTexture(), &srcRect, &destRectI);
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
