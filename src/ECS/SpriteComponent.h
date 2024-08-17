#pragma once

#include "Components.h"

#include "SDL.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() = default; // Default path is nothing
	SpriteComponent(const char* path) {
		setTexture(path);
	}

	void Init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0; // Set x and y position
		srcRect.w = srcRect.h = 32; // Set image size to 32x32
		destRect.w = destRect.h = 64; // Scales the image up to 64x64
	}

	void setTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void Update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
};