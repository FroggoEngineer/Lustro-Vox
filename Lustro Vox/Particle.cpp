#include "Particle.h"
#include <math.h>
#include <random>


Particle::Particle(float x, float y)
{
}
Particle::~Particle()
{
}

void paintParticles(std::vector<Particle>& particles, std::vector<sf::Uint8>& canvas, int width, int height)
{
	float pixel_size = round(std::max(width, height));
	for (auto p : particles) {
		int row = (int)round(p.position.x * pixel_size);
		int column = (int)round(p.position.y * pixel_size);
		canvas[row*width + column] = p.color;
	}
}

std::vector<Particle> randomParticles(int count) {
	std::vector<Particle> particles;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0, 1.0);
	auto r = [&]() { return distribution(generator); };

	for (int i{ 0 }; i < count; ++i) {
		Particle p{r(), r()};
		p.color = (rand() % 15) + 1;
		particles.push_back(p);
	}
	return particles;
}
