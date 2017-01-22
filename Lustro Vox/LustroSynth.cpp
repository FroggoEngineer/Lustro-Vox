#include "LustroSynth.h"
#include <thread>



LustroSynth::LustroSynth()
{
}


LustroSynth::~LustroSynth()
{
}

void LustroSynth::start(float * notes)
{
	tones = notes;
	run = true;
	t = std::thread(&LustroSynth::update, this);
}

void LustroSynth::stop()
{
	run = false;
	t.join();
}

void LustroSynth::update()
{
	sf::Int16 raw[BUFFER_SIZE];
	sf::SoundBuffer Buffer;
	while (run) {

		for (unsigned i{ 0 }; i < BUFFER_SIZE; ++i) {
			raw[i] = 3000 * (i % 8);
		}

		Buffer.loadFromSamples(raw, BUFFER_SIZE, 1, SAMPLE_RATE);
		sf::Sound Sound;
		Sound.setBuffer(Buffer);
		Sound.setLoop(true);
		Sound.play();
	}
}
