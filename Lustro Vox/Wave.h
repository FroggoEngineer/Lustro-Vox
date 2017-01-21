#ifndef WAVE_H
#define WAVE_H

#include <SFML/Graphics.hpp>

class Wave {

public:
	Wave(float x, float y, float forces);
	~Wave() = default;
	void update();
	float getX() { return position.x; };
	float getY() { return position.y; };
	float getRadius() { return radius; };
	float getForce() { return force; };
	sf::Vector2<float> position;
	sf::Vector2<float> getRealPos(float, float);
private:
	
	float radius{ 0.0f };
	float force{ 0.0f };

};

#endif