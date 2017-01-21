#include "Wave.h"

Wave::Wave(float x, float y, float force) {
	position.x = x;
	position.y = y;
	this->force = force;
}

void Wave::update()
{
	radius += 0.01f;
}
