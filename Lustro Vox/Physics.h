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
	void getFrame(std::vector<sf::Uint8>& frame);
	void start();
	void stop();
	void update();
private:
	sf::Mutex current_frame_lock;
	int width, height;
	unsigned int ticks;
	sf::Clock time;
	std::vector<sf::Uint8> current_frame, canvas; 
};
#endif