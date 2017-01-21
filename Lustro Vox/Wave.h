#ifndef WAVE_H
#define WAVE_H

#include <SFML/Graphics.hpp>

class Wave {

public:
	Wave(float x, float y, float force);
	~Wave() = default;
	void update();
	float getX() { return position.x; };
	float getY() { return position.y; };
	float getRadius() { return radius; };

private:
	sf::Vector2<float> position;
	float radius{ 0 };
	float force{ 0 };

};

#endif