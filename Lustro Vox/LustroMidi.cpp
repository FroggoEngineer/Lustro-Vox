#include "LustroMidi.h"
LustroMidi::LustroMidi()
{
	std::cout << midiIn.getPortCount() << std::endl;
	for (unsigned int i{ 0 }; i < midiIn.getPortCount(); ++i) {
		std::cout << midiIn.getPortName(i) << std::endl;
	}

	if (midiIn.getPortCount() > 0) {
		midiIn.openPort(0);
	}

	float notes[127];
	sound.start(notes);
}


LustroMidi::~LustroMidi()
{
	midiIn.closePort();
}

std::vector<std::pair<unsigned char, float> > LustroMidi::getNote()
{
	std::vector<std::pair<unsigned char, float> > res;
	std::vector<unsigned char> message;
	midiIn.getMessage(&message);
	while (!message.empty()) {
		if (message.size() == 3 && message[0] == 144) {
			res.push_back({ message[1] % 12, ((float)message[2]) / 127.0f });
		}


		float a = 440.0f; // a is 440 hz...
		float x = (float)message[1];
	    float freq = (a / 32.0f) * pow(2.0f,((x - 9.0f) / 12.0f));

		sound.addSquareWave(freq, 2000.0f*((float)message[2]) / 127.0f);
		midiIn.getMessage(&message);
	}

	return res;
}
