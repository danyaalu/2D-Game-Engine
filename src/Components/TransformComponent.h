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

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent()
		: position(0, 0), velocity(0, 0), height(32), width(32), scale(1), speed(3) {}

	TransformComponent(int sc)
		: position(0, 0), velocity(0, 0), height(32), width(32), scale(sc), speed(3) {}

	TransformComponent(float x, float y)
		: position(x, y), velocity(0, 0), height(32), width(32), scale(1), speed(3) {}

	TransformComponent(float x, float y, int h, int w, int sc)
		: position(x, y), velocity(0, 0), height(h), width(w), scale(sc), speed(3) {}

	void Init() override {
		velocity.x = velocity.y = 0;
	}

	void Update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
