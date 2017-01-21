#include "Physics.h"
#include "Colors.h"

Physics::Physics(int w, int h)
{
	width = w;
	height = h;
	canvas.assign(width*height, colors::BLACK);
	current_frame.assign(width*height, colors::BLACK);
}

void Physics::getFrame(std::vector<sf::Uint8>& frame) {
	current_frame_lock.lock();
	frame = current_frame;
	current_frame_lock.unlock();
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
	current_frame_lock.lock();
	std::swap(current_frame, canvas);
	current_frame_lock.unlock();
}
