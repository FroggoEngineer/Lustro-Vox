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
	void addSquareWave(float freq, float amplitude);
private:
	void update();
	int ntones;
	float* tones;
	bool run = { true };
	std::thread t;
	static const unsigned BUFFER_SIZE = 2048;
	static const unsigned SAMPLE_RATE = 44100;
	unsigned ticks{ 0 };
	void clearRaw(sf::Int16* raw);
	sf::SoundBuffer Buffer;  
	sf::Int16 raw[BUFFER_SIZE];
};

