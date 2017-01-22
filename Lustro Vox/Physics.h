#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Colors.h"
#include <thread>
#include "Particle.h"
#include "Wave.h"

class Physics {

public:
	Physics(int width, int height);
	~Physics() = default;
	void getFrame(std::vector<sf::Uint8>& frame);
	void start();
	void stop();
	void setWaves(std::vector<Wave>*);
	void addWave(Wave wave);
	void delWaves();
	void update();

private:
	float scaleX{ 0 }, scaleY{ 0 }; 
	bool run{ true };
	float gravity{ 0.0000202f };
	float waveMargin{ 0.003f };
	std::thread t;
	int width, height;
	unsigned int ticks;
	sf::Clock time;
	std::vector<sf::Uint8> current_frame, canvas; 
	std::vector<Particle> particles;
	std::vector<Wave>*waves;
};
#endif