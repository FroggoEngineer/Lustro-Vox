#include "Particle.h"
#include <math.h>
#include <random>
#include <iostream>
#include <time.h>
#include <omp.h>


Particle::Particle(float x, float y)
{
	position.x = x;
	position.y = y;
}
Particle::~Particle()
{
}

void paintParticles(std::vector<Particle>& particles, std::vector<sf::Uint8>& canvas, int width, int height)
{
	float size = (float)std::max(width, height);

	int n = particles.size();
	#pragma omp parallel for
	for (int i{ 0 }; i < n; ++i) {
		auto p = particles[i];
		int row = (int)round(p.position.x * size);
		int column = (int)round(p.position.y * size);

		int index = row * width + column;
		if (index < width*height) {
			canvas[row*width + column] = p.color; 
		}
	}
}

std::vector<Particle> randomParticles(int count) {
	std::vector<Particle> particles;

	std::default_random_engine generator(time(NULL) + rand());
	std::uniform_real_distribution<float> distribution(0.0, 1.0);
	auto r = [&]() { return distribution(generator); };

	for (int i{ 0 }; i < count; ++i) {
		Particle p{r(), r()};
		p.color = (rand() % 15) + 1;
		particles.push_back(p);
	}
	return particles;
}
