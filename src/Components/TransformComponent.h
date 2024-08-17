#pragma once
#include "Components.h"
#include "../Utilities/Vector2D.h"

/*
	TransformComponent is a struct because it has no private members
*/

struct TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height, width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent() { position.x = position.y = 0; } // Default constructor
	TransformComponent(float x, float y) { position.x = x; position.y = y; } // Constructor if position is set

	void Init() override { velocity.x = velocity.y = 0; }

	void Update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};