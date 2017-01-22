#include "LustroSynth.h"
#include <thread>
#include <iostream>
#include <math.h>



LustroSynth::LustroSynth()
{
}


LustroSynth::~LustroSynth()
{
	stop();
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
		addSquareWave(440.0f, 3000.0f);
		Buffer.loadFromSamples(raw, BUFFER_SIZE, 1, SAMPLE_RATE);
		sf::Sound Sound;

		Sound.setBuffer(Buffer);
		Sound.setLoop(true);
		Sound.play();
		while (run) {
			for (int i{ 0 }; i < BUFFER_SIZE; ++i){
				raw[i] = (int)((float)raw[i] * 0.99f);
			}
			
	//		sf::Int16* ugly = const_cast<sf::Int16*>(Buffer.getSamples());
	//		for (int i{ 0 }; i < BUFFER_SIZE; ++i) {
	//			ugly[i] = raw[i];
	//	}
	    	Buffer.loadFromSamples(raw, BUFFER_SIZE, 1, SAMPLE_RATE);
			Sound.setBuffer(Buffer);
			Sound.play();
			ticks += 1;
			sf::sleep(sf::milliseconds(10));
		}
		Sound.stop();
}

void LustroSynth::addSquareWave(float freq, float amplitude)
{
	const double TWO_PI = 6.28318;
	const double invrate = 1.0f / ((float)SAMPLE_RATE);
	auto sign = [](float x) { return (x > 0) - (x < 0); };
	for (unsigned i{ 0 }; i < BUFFER_SIZE; ++i) {
//		raw[i] += 0.3f * amplitude * sign(sin(((float)i) * freq * TWO_PI * invrate ));
		raw[i] += amplitude * cos(((float)i) * freq * TWO_PI * invrate );
		raw[i] += 0.5f * amplitude * cos(((float)i) * (freq*1.5) * TWO_PI * invrate );
	}
}

void LustroSynth::clearRaw(sf::Int16 * raw)
{
	for (int i{ 0 }; i < BUFFER_SIZE; ++i) raw[i] = 0.0f;
}
