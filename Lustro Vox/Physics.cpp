#include "Physics.h"
#include "Colors.h"

Physics::Physics(int w, int h)
{
	width = w;
	height = h;
	canvas.assign(width*height, colors::BLACK);
	current_frame.assign(width*height, colors::BLACK);
}

std::vector<sf::Uint8> Physics::getFrame()
{
	return current_frame;
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

void Physics::update()
{
	auto t = time.getElapsedTime().asMilliseconds();
	++ticks;
	canvas.assign(width*height, colors::COLORS[ticks % 16]);
	std::swap(current_frame, canvas);
}
