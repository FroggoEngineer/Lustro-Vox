#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Matrix.h"
#include "Colors.h"
#include "Physics.h"
#include "LustroMidi.h"

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 360), "SFML works!");
	sf::Vector2u size = window.getSize();

	int width = 320;
	int height = 180;

	Physics physics { width, height };

	int pixel_width = size.x / width;
	int pixel_height = size.y / height;

	sf::Uint8* canvas = new sf::Uint8[width*height];
	std::vector<sf::Uint8> frame;

	sf::RectangleShape shape(sf::Vector2f(pixel_width, pixel_height));

	sf::Uint32* pixels = new sf::Uint32[width*height];
	sf::Texture tex;

	tex.create(width, height);
	sf::Sprite sprite;
	sf::CircleShape waveShape;

	sf::Clock time;

	LustroMidi midi;

	std::vector<Wave> *waves = new std::vector<Wave>;
	Wave w{ 0.5f, 0.5f, 0.001f };
	waves->push_back(w);
	physics.addWave(waves);

	physics.start();
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			break;
		}
		
		auto notes = midi.getNote();
		for (auto note : notes) {
			std::cout << "Tone: " << (int)note.first << " Velocity: " << note.second << std::endl;
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

		// Get current frame from physics engine
		// TODO: Mutex here plox
		// UPDATE: NO MUTEX
		
		
		physics.getFrame(frame);
		for (int i{ 0 }; i < height * width; ++i) {
			pixels[i] = colors::COLORS[frame[i]];
		}


				
		tex.update((sf::Uint8*)pixels);
		
		//Pixel texture
		sprite.setTexture(tex);
		sprite.setScale(pixel_width, pixel_height);

		//Waves
		sf::Vector2<float> tmp{ 1.0f, 1.0f };
		tmp *= (*waves)[0].getRadius()*window.getSize().x;
		waveShape.setPosition((*waves)[0].getRealPos(width, height)-tmp);
		waveShape.setRadius((*waves)[0].getRadius()*window.getSize().x);
		waveShape.setOutlineThickness(2);
		waveShape.setOutlineColor(sf::Color::Green);
		waveShape.setFillColor(sf::Color::Transparent);
		


		window.draw(sprite);
		window.draw(waveShape);


		//--------------------------------------------------------------------
		window.display();
	}

	physics.stop();

	return 0;
}