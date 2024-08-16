#pragma once
#include "ECS.h"

class PositionComponent : public Component {
private:
	int xpos;
	int ypos;

public:
	int x() const { return xpos; }
	int y() const { return ypos; }

	void Init() override { xpos = ypos = 0; }

	void Update() override {
		xpos++;
		ypos++;
	}

	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}


};