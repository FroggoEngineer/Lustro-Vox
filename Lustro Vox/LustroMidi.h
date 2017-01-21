#pragma once
#include "rtmidi-2.1.1\RtMidi.h"

class LustroMidi
{
public:
	LustroMidi();
	~LustroMidi();
	std::pair<unsigned char, unsigned char> getNote();

private:
	RtMidiIn midiIn;
	std::vector<unsigned char> messages;
};

