#ifndef COLORS_H
#define COLORS_H
#include <SFML/Graphics.hpp>

namespace colors {
	static const sf::Uint32 reverse_byte_order(sf::Uint32 col) {
		sf::Uint32 r = (col & 0x000000ff) << 24;
		sf::Uint32 g = (col & 0x0000ff00) << 8;
		sf::Uint32 b = (col & 0x00ff0000) >> 8;
		sf::Uint32 a = (col & 0xff000000) >> 24;

		return r | g | b | a;
	}


	static const sf::Uint32 COLORS[16] = {
	reverse_byte_order(0x002b36ff),
	reverse_byte_order(0xb58900ff),
	reverse_byte_order(0xcb4b16ff),
	reverse_byte_order(0xdc322fff),
	reverse_byte_order(0xd33682ff),
	reverse_byte_order(0x6c71c4ff),
	reverse_byte_order(0x268bd2ff),
	reverse_byte_order(0x2aa198ff),
	reverse_byte_order(0x859900ff),
	reverse_byte_order(0x859900ff),
	reverse_byte_order(0x859900ff),
	reverse_byte_order(0x859900ff),
	reverse_byte_order(0x859900ff),
	reverse_byte_order(0x859900ff),
	reverse_byte_order(0x859900ff),
	reverse_byte_order(0x859900ff),
	};

	static const sf::Uint8 BLACK = 0;
};


#endif
