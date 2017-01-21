#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1, 1), "SFML works!", sf::Style::Fullscreen);
	
	sf::RectangleShape shape(sf::Vector2f(10,10));

	shape.setFillColor(sf::Color::Green);

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



		window.draw(shape);




		//--------------------------------------------------------------------
		window.display();
	}

	return 0;
}