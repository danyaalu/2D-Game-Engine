#pragma once

#include "SDL.h"
#include "../Components/ColliderComponent.h"

class Collision {
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
		return SDL_HasIntersection(&recA, &recB);
	}
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB) {
		if (AABB(colA.collider, colB.collider)) {
			if (colA.tag != colB.tag) {
				std::cout << colA.tag << " hit: " << colB.tag << std::endl;
				return true;
			}
		}
		else {
			return false;
		}
	}
};