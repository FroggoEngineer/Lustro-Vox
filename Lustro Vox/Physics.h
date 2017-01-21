#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>

class Physics {

public:
	Physics() = default;
	~Physics() = default;
	sf::Uint8* getFrame() {};
	void start();
	void stop();
private:
	sf::Uint8* glob{ nullptr }; 
	sf::Uint8* calcCanvas{ nullptr };
	void update();

};


#endif