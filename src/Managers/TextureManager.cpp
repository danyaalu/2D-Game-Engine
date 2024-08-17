#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture); // Creates temporary surface to load sprite
	if (!tempSurface) {
		std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
		return nullptr;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface); // Creates texture from the temporary surface

	// Frees temporary surface
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}