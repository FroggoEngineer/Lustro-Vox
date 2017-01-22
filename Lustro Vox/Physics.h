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

private:
	void update();
	float scaleX{ 0 }, scaleY{ 0 }; 
	bool run{ true };
	float gravity{ 0.0000102f };
	float waveMargin{ 0.001f };
	std::thread t;
	sf::Mutex current_frame_lock;
	sf::Mutex waves_lock;
	int width, height;
	unsigned int ticks;
	sf::Clock time;
	std::vector<sf::Uint8> current_frame, canvas; 
	std::vector<Particle> particles;
	std::vector<Wave>*waves;
};
#endif