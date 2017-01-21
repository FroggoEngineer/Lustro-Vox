#pragma once
#include "rtmidi-2.1.1\RtMidi.h"

class LustroMidi
{
public:
	LustroMidi();
	~LustroMidi();
	std::vector<std::pair<unsigned char, float> > getNote();

private:
	RtMidiIn midiIn;
};

