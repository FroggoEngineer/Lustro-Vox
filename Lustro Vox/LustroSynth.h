#pragma once
#include <thread>
#include "SFML\Audio.hpp"

class LustroSynth
{
public:
	LustroSynth();
	~LustroSynth();
	void start(float* notes);
	void stop();
private:
	void update();
	float* tones;
	bool run = { true };
	std::thread t;
	static const unsigned BUFFER_SIZE = 44100;
	static const unsigned SAMPLE_RATE = 44100;
	unsigned time{ 0 };
};

