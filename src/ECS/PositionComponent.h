#pragma once
#include "Components.h"

class PositionComponent : public Component {
private:
	int xpos;
	int ypos;

public:

	PositionComponent() { xpos = 0; ypos = 0; } // Default constructor
	PositionComponent(int x, int y) { xpos = x; ypos = y; } // Constructor if position is set

	void Update() override {
		xpos++;
		ypos++;
	}

	// Functions for getting position
	int x() const { return xpos; }
	int y() const { return ypos; }

	// Functions for setting position
	void x(int x) { xpos = x; }
	void y(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }
};