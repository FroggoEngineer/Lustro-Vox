#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Colors.h"
#include <thread>
class Physics {

public:
	Physics(int width, int height);
	~Physics() = default;
	std::vector<sf::Uint8> getFrame();
	void start();
	void stop();
	
private:
	void update();
	bool run{ true };
	std::thread t;
	int width, height;
	unsigned int ticks;
	sf::Clock time;
	std::vector<sf::Uint8> current_frame, canvas; 
};
#endif