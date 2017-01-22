#include "Physics.h"
#include "Colors.h"
#include "Particle.h"
#include <iostream>
#include <thread>
#include <random>
#include <time.h>
#include <SFML/System.hpp>
#include <math.h>

Physics::Physics(int w, int h)
{
	width = w;
	height = h;
	canvas.assign(width*height, colors::BLACK);
	current_frame.assign(width*height, colors::BLACK);
	particles = randomParticles(0);
}

void Physics::getFrame(std::vector<sf::Uint8>& frame) {
	frame = current_frame;
}

void Physics::start()
{
	t = std::thread(&Physics::update, this);
}

void Physics::stop()
{
	run = false;
	t.join();
}

void Physics::setWaves(std::vector<Wave>* waveVec)
{
	waves = waveVec;
}

void Physics::addWave(Wave wave)
{
	waves->push_back(wave);
}

void Physics::delWaves()
{
	int i{ 0 };
	while (i < waves->size()) {
		if ((*waves)[i].getRadius() > 0.1f) {
			(*waves)[i] = waves->back();
			waves->pop_back();
		}
		else {
			++i;
		}
	}
}


void Physics::update()
{
		sf::Clock time;
		++ticks;
		canvas.assign(width*height, colors::BLACK);

		while (particles.size() > 20000) {
			if (partIndex >= particles.size())
				partIndex = 0;

			particles[partIndex] = particles.back();
			particles.pop_back();

			partIndex++;
		}


		int n = particles.size();

		//Update waves
		for (int i{ 0 }; i < waves->size(); ++i) {
			(*waves)[i].update();
		}

		//Update forces on particles from waves
		for (auto w : (*waves)) {
			#pragma simd
			#pragma omp parallel for
			for (int i{ 0 }; i < n; ++i) {
				auto &p = particles[i];
				
				float distance = sqrt(pow((p.getX() - w.getX()), 2) + pow((p.getY() - w.getY()), 2));
				
				if (distance < (w.getRadius() + waveMargin) && distance >(w.getRadius() - waveMargin)) {
					sf::Vector2<float> forceExert = p.position - w.position;
					forceExert *= w.getForce();
					p.exertForce(forceExert/(50*w.getRadius()));
				}

			}
		}


		//Update gravity and air resistance
		#pragma simd
		#pragma omp parallel for
		for (int i{ 0 }; i < n; ++i) {

			auto &p = particles[i];
			p.updateForces(gravity);
			p.move();
			
			if (p.getY() > 0.5f) {
				float sidediff = (((float)i) / ((float)n) * 2 - 1) * 1.0;
				p.speed.y = -1.0 * (float)abs(p.speed.y);
				p.speed.y *= abs(sidediff);
				//p.speed.x += sidediff*p.speed.y;
			}
			else if (p.getY() <= 0.001f) {
				float sidediff = (((float)i) / ((float)n) * 2 - 1) * 1.0;
				p.speed.y = (float)abs(p.speed.y);
				p.speed.y *= abs(sidediff);
				//p.speed.x += sidediff*p.speed.y;
			}
			else if (p.getX() <= 0.00f) {
				p.speed.x = (float)abs(p.speed.x);
			}
			else if (p.getX() > 1.0f) {
				p.speed.x = -1 * (float)abs(p.speed.x);
			}
		}
		//Paint particles to canvas
		paintParticles(particles, canvas, width, height);
		
		//Send the new canvas out for rendering
		std::swap(current_frame, canvas);
}

void Physics::addParticles(int amount, float x, float y)
{

	std::default_random_engine generator(std::time(NULL) + rand());
	std::uniform_real_distribution<float> distributionX(-1.0, 1.0);
	std::uniform_real_distribution<float> distributionY(0.5, 1.0);
	auto rx = [&]() { return distributionX(generator); };
	auto ry = [&]() { return distributionY(generator); };

	for (int i{ 0 }; i < amount; ++i) {
		Particle p{ x,y };
		p.speed.x = 0.005f * rx();
		p.speed.y = 0.005f * ry();
		p.color = (rand() % 15) + 1;
		particles.push_back(p);

	}
}

void Physics::spawnParticles(int amount)
{
	particles = randomParticles(amount);
}

