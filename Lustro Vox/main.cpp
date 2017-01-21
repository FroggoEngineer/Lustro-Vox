#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Colors.h"

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(320, 180), "SFML works!", sf::Style::Fullscreen);
	sf::Vector2u size = window.getSize();

	int width = 320;
	int height = 180;


	int pixel_width = size.x / width;
	int pixel_height = size.y / height;

	sf::Uint8* canvas = new sf::Uint8[width*height];

	sf::RectangleShape shape(sf::Vector2f(pixel_width, pixel_height));

	sf::Uint32* pixels = new sf::Uint32[width*height];
	sf::Texture tex;

	tex.create(width, height);
	sf::Sprite sprite;

	sf::Clock time;
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			break;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}



			//Input events
			//---------------------------------------------------
			


			//---------------------------------------------------

		}


		window.clear();
		//Rendering
		//--------------------------------------------------------------------

		for (int i{ 0 }; i < height * width; ++i) {
			pixels[i] = COLORS[i%4];
		}
				
		tex.update((sf::Uint8*)pixels);
	
		sprite.setTexture(tex);
		sprite.setScale(pixel_width, pixel_height);

		window.draw(sprite);


		//--------------------------------------------------------------------
		window.display();
	}

	return 0;
}