#include "Wave.h"

Wave::Wave(float x, float y, float forces) {
	position.x = x;
	position.y = y;
	force = forces;
}

void Wave::update()
{
	radius += 0.0001f;
}

sf::Vector2<float> Wave::getRealPos(float width, float height)
{
	sf::Vector2<float> tmp = position;
	tmp.x *= width;
	tmp.y *= height;
	return tmp;
}
