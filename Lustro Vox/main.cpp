#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1, 1), "SFML works!", sf::Style::Fullscreen);
	sf::Vector2u size = window.getSize();

	int width = 320;
	int height = 180;


	int pixel_width = size.x / width;
	int pixel_height = size.y / height;

	sf::RectangleShape shape(sf::Vector2f(pixel_width, pixel_height));

	shape.setFillColor(sf::Color::Green);
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
		shape.setPosition(0, 0);
		//Rendering
		//--------------------------------------------------------------------

		for (int i{ 0 }; i < width; i++)
			for (int j{ 0 }; j < height; j++) {
				int r = (int)round((sin(j)+1)*127);
				int g = (int)round((cos(i)+1)*127);
				int b = (int)round(time.getElapsedTime().asMilliseconds()%256);

				shape.setFillColor(sf::Color(r, g, b));
				shape.setPosition(i*pixel_width, j*pixel_height);
			}
				
		window.draw(shape);




		//--------------------------------------------------------------------
		window.display();
	}

	return 0;
}