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
// 0xAABBGGRR
reverse_byte_order(0xff0000ff),
reverse_byte_order(0x00ff00ff),
reverse_byte_order(0x0000ffff),
reverse_byte_order(0xffffffff),
reverse_byte_order(0x0087ffff),
reverse_byte_order(0xaf005fff),
reverse_byte_order(0x1c1c1cff),
reverse_byte_order(0xd75f00ff),
reverse_byte_order(0x00afafff),
reverse_byte_order(0xe4e4e4ff),
reverse_byte_order(0x1c1c1cff),
reverse_byte_order(0xd75f00ff),
reverse_byte_order(0x585858ff),
reverse_byte_order(0x626262ff),
reverse_byte_order(0x808080ff),
reverse_byte_order(0x5f5fafff),
};

