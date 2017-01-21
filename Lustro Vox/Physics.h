#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Colors.h"

class Physics {

public:
	Physics(int width, int height);
	~Physics() = default;
	std::vector<sf::Uint8> getFrame();
	void start();
	void stop();
	void update();
private:
	int width, height;
	unsigned int ticks;
	sf::Clock time;
	std::vector<sf::Uint8> current_frame, canvas; 
};
#endif