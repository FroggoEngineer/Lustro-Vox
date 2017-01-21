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
	reverse_byte_order(0x000000ff),
	reverse_byte_order(0xFFFFFFff),
	reverse_byte_order(0x68372Bff),
	reverse_byte_order(0x70A4B2ff),
	reverse_byte_order(0x6F3D86ff),
	reverse_byte_order(0x588D43ff),
	reverse_byte_order(0x352879ff),
	reverse_byte_order(0xB8C76Fff),
	reverse_byte_order(0x6F4F25ff),
	reverse_byte_order(0x433900ff),
	reverse_byte_order(0x9A6759ff),
	reverse_byte_order(0x444444ff),
	reverse_byte_order(0x6C6C6Cff),
	reverse_byte_order(0x9AD284ff),
	reverse_byte_order(0x6C5EB5ff),
	reverse_byte_order(0x95959ff5)
	};

	static const sf::Uint8 BLACK = 0;
};


#endif
