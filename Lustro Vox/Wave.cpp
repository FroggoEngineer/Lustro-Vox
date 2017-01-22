#include "Wave.h"

Wave::Wave(float x, float y, float forces, float rate) {
	position.x = x;
	position.y = y;
	force = forces;
	expansion_rate = rate;
}

void Wave::update()
{
	radius += expansion_rate;
}

sf::Vector2<float> Wave::getRealPos(float width, float height)
{
	sf::Vector2<float> tmp = position;
	tmp.x *= width;
	tmp.y *= height;
	return tmp;
}
