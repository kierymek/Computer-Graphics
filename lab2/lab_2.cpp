#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Slider.h"
#include "RGB.h"
#include "HSL.h"
#include "HSV.h"
#include "CMY.h"


extern unsigned char font_data[500000];
extern unsigned int font_data_size;

int main()
{
	sf::RenderWindow window(sf::VideoMode(750, 650), "GFK Lab 02 Adrian Góral", sf::Style::Titlebar | sf::Style::Close);

	sf::Clock clock;
	sf::Time time = sf::Time::Zero;
	unsigned int FPS = 0, frame_counter = 0;

	sf::Text FPSText;
	HSL hsl;
	CMY cmy;
	RGB rgb;
	HSV hsv;

	Slider slider(40, 300);

	sf::Font font;
	font.loadFromMemory(font_data, font_data_size);

	FPSText.setFont(font);
	FPSText.setCharacterSize(13);

	FPSText.setStyle(sf::Text::Regular);

	FPSText.setFillColor(sf::Color::Black);

	FPSText.setPosition(670, 440);


	//inicjalizacja 
	clock.restart().asMilliseconds();
	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
			// zdarzenia
			switch (event.type)
			{
			case sf::Event::Closed: 
				window.close();
				break;
	
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)	window.close();
				break;

			case sf::Event::MouseMoved:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					slider.updatePosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				break;

			case sf::Event::MouseButtonReleased:
					slider.updatePosition(sf::Vector2f(sf::Mouse::getPosition(window)));
				break;
			default: break;
			}
		}

		//tu wyrysować wszystko na ekran
		float parameter = slider.get_parameter();

		rgb.modify(parameter);

		window.draw(rgb);

		hsl.modify(parameter);
		window.draw(hsl);

		cmy.modify(parameter);
		window.draw(cmy);

		hsv.modify(parameter);
		window.draw(hsv);

		window.draw(slider);

		//tu wypisać na ekran wartość FPS

		FPSText.setString("FPS: " + conv_to_string(FPS, 0));
		window.draw(FPSText);

		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;

		window.display();
	}
}