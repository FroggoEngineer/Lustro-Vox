#pragma once
#include <SFML/Graphics.hpp>
#include "Colors.h"
class Particle
{
public:
	Particle(float x, float y);
	~Particle();
	sf::Vector2<float> position;
	sf::Uint8 color = colors::BLACK;
	sf::Vector2<float> speed;
	float getX() { return position.x; };
	float getY() { return position.y; };
	void updateForces(float grav);
	void move();

};
void paintParticles(std::vector<Particle>& particles, std::vector<sf::Uint8>& canvas, int width, int height);
std::vector<Particle> randomParticles(int count);
