#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(texture); // Creates temporary surface to load sprite
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface); // Creates texture from the temporary surface

	// Frees temporary surface
	SDL_FreeSurface(tempSurface);

	return tex;
}