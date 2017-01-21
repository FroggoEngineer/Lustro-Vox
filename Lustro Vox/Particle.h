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
};

