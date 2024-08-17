#pragma once

#include "Components.h"
#include "../Managers/TextureManager.h"
#include "SDL.h"

class SpriteComponent : public Component {
public:
	SpriteComponent() = default; // Default path is nothing
	SpriteComponent(const char* path) {
		setTexture(path);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void Init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0; // Set x and y position
		srcRect.w = transform->width; // Set width
		srcRect.h = transform->height; // Set height
	}

	void setTexture(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void Update() override {
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
};