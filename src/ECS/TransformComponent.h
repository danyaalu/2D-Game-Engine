#pragma once
#include "Components.h"
#include "../Vector2D.h"

/*
	TransformComponent is a struct because it has no private members
*/

struct TransformComponent : public Component {
public:
	Vector2D position;

	TransformComponent() { position.x = position.y = 0; } // Default constructor
	TransformComponent(float x, float y) { position.x = x; position.y = y; } // Constructor if position is set

	void Update() override {

	}
};