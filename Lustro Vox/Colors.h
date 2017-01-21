#pragma once
#include <SFML/Graphics.hpp>

sf::Uint32 reverse_byte_order(sf::Uint32 col) {
	sf::Uint32 r = (col & 0x000000ff) << 24;
	sf::Uint32 g = (col & 0x0000ff00) << 8;
	sf::Uint32 b = (col & 0x00ff0000) >> 8;
	sf::Uint32 a = (col & 0xff000000) >> 24;

	return r | g | b | a;
}

sf::Uint32 COLORS[16] = {
reverse_byte_order(0x000000),
reverse_byte_order(0xFFFFFF),
reverse_byte_order(0x68372B),
reverse_byte_order(0x70A4B2),
reverse_byte_order(0x6F3D86),
reverse_byte_order(0x588D43),
reverse_byte_order(0x352879),
reverse_byte_order(0xB8C76F),
reverse_byte_order(0x6F4F25),
reverse_byte_order(0x433900),
reverse_byte_order(0x9A6759),
reverse_byte_order(0x444444),
reverse_byte_order(0x6C6C6C),
reverse_byte_order(0x9AD284),
reverse_byte_order(0x6C5EB5),
reverse_byte_order(0x959595)
};

