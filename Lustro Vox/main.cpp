#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <random>
#include <time.h>
#include "Matrix.h"
#include "Colors.h"
#include "Physics.h"
#include "LustroMidi.h"

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 360), "SFML works!");
	sf::Vector2u size = window.getSize();
	int scaleWidth = size.x;
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

	int tick{ 0 };

	LustroMidi midi;

	std::vector<Wave> *waves = new std::vector<Wave>;
	physics.setWaves(waves);

	window.setVerticalSyncEnabled(true);

	sf::Shader shader;

	if (shader.loadFromFile("rage.frag", sf::Shader::Fragment))
	{
		
	}

	if (sf::Joystick::isConnected(0))
	{
		// joystick number 0 is connected
		cout << "Joystick connected on 0: " << sf::Joystick::isConnected(0) << endl;
		cout << "Joystick connected on 1: " << sf::Joystick::isConnected(1) << endl;
		cout << sf::Joystick::getIdentification << endl;
	}

	sf::RectangleShape player1;
	sf::RectangleShape player2;
	player1.setPosition(180, 5);
	player2.setPosition(180, 100);

	std::default_random_engine generator(std::time(NULL) + rand());
	std::uniform_real_distribution<float> distributionX(0.1, 0.3);
	std::uniform_real_distribution<float> distributionY(0.2, 0.8);
	auto shader_rnd = [&]() { return distributionX(generator); };
	auto shader_intensity = [&]() { return distributionY(generator); };



	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			break;
		}
		
		auto notes = midi.getNote();
		for (auto note : notes) {
			std::cout << "Tone: " << (int)note.first << " Velocity: " << note.second << std::endl;
			Wave w1{ ((float)note.first)/11.0f, 0.5626f, 0.4f*note.second, 0.01f*note.second };
			physics.addWave(w1);
		}


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}



			

		}
		//Input events
		//---------------------------------------------------
		float topAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X);


		if (topAxis > 30) {
			sf::Vector2<float> tmp = player1.getPosition();
			tmp.x = tmp.x + 5;
			player1.setPosition(tmp);
		}
		else if (topAxis < -30) {
			sf::Vector2<float> tmp = player1.getPosition();
			tmp.x = tmp.x - 5;
			player1.setPosition(tmp);
		}


		if (sf::Joystick::isButtonPressed(0, 1)) {
			physics.addParticles(50, (player1.getPosition().x + 5.f) / (float)640, (player1.getPosition().y + 10.f) / (float)640);
		}
		else if (sf::Joystick::isButtonPressed(0, 3)) {
			physics.spawnParticles(10000);
		}



		//---------------------------------------------------

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
		
		
		//Pixel texture
		sprite.setTexture(tex);
		sprite.setScale(pixel_width, pixel_height);

		window.draw(sprite);

		// Remove too large waves
		if (tick % 60 == 0) {
			physics.delWaves();

		}

		player1.setSize(sf::Vector2<float>(10*pixel_width, 10*pixel_height));
		player1.setFillColor(sf::Color::Red);
		window.draw(player1);


		//Waves
		for (int i{ 0 }; i < waves->size(); ++i) {
			sf::Vector2<float> tmp{ 1.0f, 1.0f };
			tmp *= (*waves)[i].getRadius()*scaleWidth;
			waveShape.setPosition(((*waves)[i].getRealPos(scaleWidth, scaleWidth)-tmp)); // Don't ask...
			waveShape.setRadius((*waves)[i].getRadius()*scaleWidth);
			waveShape.setOutlineThickness(scaleWidth/100);
			waveShape.setOutlineColor(sf::Color(colors::COLORS[(i%15)+1]));

			waveShape.setFillColor(sf::Color::Transparent);
			shader.setUniform("rnd", 0.5f);
			shader.setUniform("intensity", 0.8f);
			window.draw(waveShape, &shader);
		}

		//--------------------------------------------------------------------
		++tick;
		window.display();

		

	}


	return 0;
}