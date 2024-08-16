#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y) {
	objectTexture = TextureManager::LoadTexture(textureSheet); // Load the texture

	xpos = x;
	ypos = y;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	// Define the source rectangle (portion of the texture to use)
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	// Define the destination rectangle (where to render the texture on the screen)
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2; // Scale width by 2
	destRect.h = srcRect.h * 2; // Scale width by 2

}

void GameObject::Render() {
	// Copy the texture to the rendering context
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}