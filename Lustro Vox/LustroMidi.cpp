#include "LustroMidi.h"
LustroMidi::LustroMidi()
{
	std::cout << midiIn.getPortCount() << std::endl;
	std::cout << midiIn.getPortName(0) << std::endl;
	if (midiIn.getPortCount() > 0) {
		midiIn.openPort();
	}
}


LustroMidi::~LustroMidi()
{
	midiIn.closePort();
}

std::pair<unsigned char, unsigned char> LustroMidi::getNote()
{
	while (!messages.empty()) {
		std::cout << (int)messages.back() << std::endl;
		messages.pop_back();
	}
	midiIn.getMessage(&messages);
	return { 0,0 };
}
