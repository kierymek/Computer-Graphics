#include "DrawShapes.h"
#include <cmath>
#include <tgmath.h>


//usuwa obiekty w kontenerze
drawShapes::~drawShapes()
{
	for (auto &p : _shapes)
		delete p;
}


//wrzuca obiekty do kontenera pozniej sa one rysowane
void drawShapes::addShape(sf::Drawable * shape)
{
	_shapes.push_back(shape);
}


//rysowanie kolejnych kszta³tów
void drawShapes::drawLine()
{
	sf::VertexArray *line = new sf::VertexArray(sf::LinesStrip, 2);
	(*line)[0] = sf::Vertex(_hp->mouseClickPos, _menu->getForegroundColor());
	(*line)[1] = sf::Vertex(_hp->mousePos, _menu->getBackgroundColor());

	_window->draw(*line);

	if (_hp->mouseReleased)
		addShape(line);
	else delete line;
}

void drawShapes::drawRectangle(bool filling)
{
	sf::RectangleShape * rectangle = new sf::RectangleShape(_hp->mousePos - _hp->mouseClickPos);
	rectangle->setPosition(_hp->mouseClickPos);
	rectangle->setOutlineColor(_menu->getForegroundColor());
	rectangle->setOutlineThickness(1);
	if (filling)
		rectangle->setFillColor(_menu->getBackgroundColor());
	else
		rectangle->setFillColor(sf::Color::Transparent);

	_window->draw(*rectangle);

	if (_hp->mouseReleased)
		addShape(rectangle);
	else
		delete rectangle;
}

void drawShapes::drawCircle()
{
	sf::CircleShape *circle = new sf::CircleShape;
	float radius = sqrt(pow(_hp->mousePos.x - _hp->mouseClickPos.x, 2) + pow(_hp->mousePos.y - _hp->mouseClickPos.y, 2)) / 2.;
	circle->setRadius(radius);
	circle->setFillColor(sf::Color::Transparent);
	circle->setOutlineColor(_menu->getForegroundColor());
	circle->setOutlineThickness(1);
	circle->setPosition(sf::Vector2f(_hp->mouseClickPos.x, _hp->mouseClickPos.y));
	float angle = atan2((_hp->mousePos.y - _hp->mouseClickPos.y), (_hp->mousePos.x - _hp->mouseClickPos.x))*(180/3.1415) - 45;
	circle->rotate(angle);
	circle->move(sf::Vector2f((radius - radius * sqrt(2)) * cos((angle + 45) * 3.1415 / 180), (radius - radius * sqrt(2)) * sin((angle + 45) * 3.1415 / 180)));
	_window->draw(*circle);
	
	if (_hp->mouseReleased)
		addShape(circle);
	else
		delete circle;
}

//rysowanie obiektow z kontenera
void drawShapes::draw()
{
	for (auto &p : _shapes)
		_window->draw(*p);
}


//zapis do pliku
void drawShapes::saveToFile()
{
	sf::Texture newTexture;
	newTexture.create(_window->getSize().x, _window->getSize().y);
	newTexture.update(*_window);
	sf::Image image;
	image.create(796, 536, sf::Color::Black);
	image.copy(newTexture.copyToImage(), 0, 0, sf::IntRect(2, 62, 796, 536));
	image.saveToFile("result.jpg");
	_hp->isKeyPressed = false;
	_menu->keyPressed();
}

//za³adowanie z pliku
void drawShapes::loadFromFile(sf::Texture& texture)
{
	sf::Image image;
	if (image.loadFromFile("result.jpg")) {
		texture.loadFromImage(image);
		sf::Sprite newWorkspace(texture);
		newWorkspace.setPosition(sf::Vector2f(2, 62));
		addShape(new sf::Sprite(newWorkspace));
	}
	_hp->isKeyPressed = false;
	_menu->keyPressed();
}