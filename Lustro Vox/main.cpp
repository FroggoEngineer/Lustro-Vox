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
	sf::RenderWindow window(sf::VideoMode(640, 360), "SFML works!", sf::Style::Fullscreen);
	sf::Vector2u size = window.getSize();

	int width = 160;
	int height = 90;

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

	int tick{ 0 };

	LustroMidi midi;

	std::vector<Wave> *waves = new std::vector<Wave>;
	physics.setWaves(waves);

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
			Wave w1{ ((float)note.first)/11.0f, 0.5626f, 0.1f*note.second, 0.003f/note.second };
			physics.addWave(w1);
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
		// UPDATE: NO THREADS

		physics.update();
		
		
		physics.getFrame(frame);

		#pragma omp parallel for
		for (int i{ 0 }; i < height * width; ++i) {
			pixels[i] = colors::COLORS[frame[i]];
		}


				
		tex.update((sf::Uint8*)pixels);
		window.draw(sprite);
		
		//Pixel texture
		sprite.setTexture(tex);
		sprite.setScale(pixel_width, pixel_height);

		// Remove too large waves
		if (tick % 60 == 0) {
			physics.delWaves();

		}

		//Waves
		for (int i{ 0 }; i < waves->size(); ++i) {
			sf::Vector2<float> tmp{ 1.0f, 1.0f };
			tmp *= (*waves)[i].getRadius()*window.getSize().x;
			waveShape.setPosition(((*waves)[i].getRealPos(window.getSize().x, window.getSize().x)-tmp)); // Don't ask...
			waveShape.setRadius((*waves)[i].getRadius()*window.getSize().x);
			waveShape.setOutlineThickness(window.getSize().x/100);
			waveShape.setOutlineColor(sf::Color(colors::COLORS[(i%15)+1]));

			waveShape.setFillColor(sf::Color::Transparent);

			window.draw(waveShape);
		}

		//--------------------------------------------------------------------
		++tick;
		window.display();

	}


	return 0;
}