#include "Map.h"
#include "../Managers/TextureManager.h"

int lvl1[20][25] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};


Map::Map() {
	dirt = TextureManager::LoadTexture("assets/images/dirt.png");
	grass = TextureManager::LoadTexture("assets/images/grass.png");
	water = TextureManager::LoadTexture("assets/images/water.png");

	LoadMap(lvl1);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}

Map::~Map() {
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(dirt);
}

void Map::LoadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {
			map[row][col] = arr[row][col];
		}
	}
}

void Map::DrawMap() {
	int type = 0;

	for (int row = 0; row < 20; row++) {  // Corrected loop condition
		for (int col = 0; col < 25; col++) {
			type = map[row][col];

			dest.x = col * 32;
			dest.y = row * 32;

			switch (type) {
			case 0:
				TextureManager::Draw(water, src, dest);
				break;  // Added break
			case 1:
				TextureManager::Draw(dirt, src, dest);
				break;  // Added break
			case 2:
				TextureManager::Draw(grass, src, dest);
				break;  // Added break
			default:
				break;
			}
		}
	}
}