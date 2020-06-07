
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "DrawShapes.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01 - Adrian Góral", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	Menu menu;
	helper hp;
	window.setFramerateLimit(60);
	sf::Texture texture;
	drawShapes shape(&window, &menu, &hp);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			else if (event.type == sf::Event::KeyPressed)
			{
				hp.mouseClickedOnColors = hp.mouseClickedOnWorkspace = false;
				hp.isKeyPressed = true;
				menu.keyPressed(event.key.code);
				hp.keyPressed = event.key.code;
				if (event.key.code == sf::Keyboard::Key::Escape)window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				hp.mouseClickPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
				hp.mouseClickedOnColors = menu.mouseOnColors(hp.mouseClickPos);
				hp.mouseClickedOnWorkspace = menu.mouseOnWorkspace(hp.mouseClickPos);
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				hp.mouseReleased = true;
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (menu.mouseOnWorkspace(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					hp.mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			}
		}

		//wklejenie obiektu rysowanego po puszczeniu przycisku myszy
		shape.draw();

		//rysowanie kształtów
		if (hp.isKeyPressed)
		{
			if (hp.mouseClickedOnWorkspace)
			{
				switch (hp.keyPressed)
				{
				case sf::Keyboard::Key::L:
					shape.drawLine();
					break;
				case sf::Keyboard::Key::R:
					shape.drawRectangle();
					break;
				case sf::Keyboard::Key::A:
					shape.drawRectangle(true);
					break;
				case sf::Keyboard::Key::C:
					shape.drawCircle();
					break;
				default:
					break;
				}
			}
		}

		//obsluga palety kolorow
		if (hp.mouseClickedOnColors)
		{
			switch (hp.keyPressed)
			{
			case sf::Keyboard::Key::F:
				menu.setForegroundColor(menu.takeColor(hp.mouseClickPos));
				break;
			case sf::Keyboard::Key::B:
				menu.setBackgroundColor(menu.takeColor(hp.mouseClickPos));
				break;
			default:
				break;
			}
			hp.mouseClickedOnColors = false;
		}

		if (hp.mouseReleased)
		{
			hp.mouseClickedOnWorkspace = hp.mouseReleased = false;
		}

		switch (hp.keyPressed)
		{
		case sf::Keyboard::Key::W:
			shape.saveToFile();
			break;
		case sf::Keyboard::Key::O:
			shape.loadFromFile(texture);
			break;
		default: break;
		}

		window.draw(menu);
		window.display();

	}
	return 0;
}