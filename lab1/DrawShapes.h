#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Menu.h"


//klasa pomocnicza pomagajaca w rysowaniu obiektow
class helper
{
public:	
	bool mouseClickedOnWorkspace = false;
	bool mouseClickedOnColors = false;
	bool mouseReleased = false;
	bool isKeyPressed = false;

	sf::Vector2f mouseClickPos;
	sf::Vector2f mousePos;
	sf::Keyboard::Key keyPressed;

};

class drawShapes
{
public:
	drawShapes(sf::RenderWindow * window, Menu * menu, helper * hp) : _hp(hp), _menu(menu), _window(window) {}
	~drawShapes();

	//dzialania rysowania i zapisu
	void addShape(sf::Drawable * shape);
	void drawLine();
	void drawRectangle(bool filling = false);
	void drawCircle();
	void draw();
	void saveToFile();
	void loadFromFile(sf::Texture& texture);

private:
	Menu * _menu;
	helper * _hp;
	sf::RenderWindow * _window;
	std::vector <sf::Drawable *> _shapes;

};
