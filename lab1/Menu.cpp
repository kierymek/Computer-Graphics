#include "Menu.h"
#include "font.h"


Menu::Menu()
{
	font.loadFromMemory(font_data, font_data_size);
	text = new sf::Text;
	text->setFont(font);
	text->setCharacterSize(12);
	text->setFillColor(sf::Color::White);

	//tutuł wykonywanego działania
	title = new sf::Text;
	title->setFont(font);
	title->setCharacterSize(12);
	title->setFillColor(sf::Color::White);

	_foregroundColor = sf::Color::Black;
	_backgroundColor = sf::Color::Transparent;

	rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
	rectangle->setFillColor(sf::Color::Transparent);
	rectangle->setOutlineColor(sf::Color::White);
	rectangle->setOutlineThickness(1.0f);
	rectangle->setPosition(2, 62);

	unsigned int x, y;
	colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
	for (x = 0; x < 255; x++)
		for (y = 0; y < 30; y++)
		{
			draw_to_color_pixels(x, y, x, 255, 0);
			draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
			draw_to_color_pixels(x + 510, y, 255, 0, x);
			draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
			draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
			draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
		}

	colors_texture = new sf::Texture();
	colors_texture->create(colors_size_x, colors_size_y);
	colors_texture->update(colors_pixels);

	colors_sprite = new sf::Sprite();
	colors_sprite->setTexture(*colors_texture);
	colors_sprite->setPosition(1, 1);

	rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
	rectangle->setFillColor(sf::Color::Transparent);
	rectangle->setOutlineColor(sf::Color::White);
	rectangle->setOutlineThickness(1.0f);
	rectangle->setPosition(2, 62);

	//wypełnienie kwadratów wyboru kolorów linni i wypełnienia
	_drawingColorRectangle = new sf::RectangleShape(sf::Vector2f(800. - colors_size_x - 2., colors_size_y / 2. - 2.));
	_drawingColorRectangle->setFillColor(_foregroundColor);
	_drawingColorRectangle->setPosition(colors_size_x + 2, 2);
	_fillingColorRectangle = new sf::RectangleShape(sf::Vector2f(800. - colors_size_x - 2., colors_size_y / 2. - 2.));
	_fillingColorRectangle->setFillColor(_backgroundColor);
	_fillingColorRectangle->setPosition(colors_size_x + 2., colors_size_y / 2. + 2.);
}

void Menu::keyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::F:
		_keyPressed = 'f';
		break;
	case sf::Keyboard::B:
		_keyPressed = 'b';
		break;
	case sf::Keyboard::L:
		_keyPressed = 'l';
		break;
	case sf::Keyboard::R:
		_keyPressed = 'r';
		break;
	case sf::Keyboard::A:
		_keyPressed = 'a';
		break;
	case sf::Keyboard::C:
		_keyPressed = 'c';
		break;
	case sf::Keyboard::W:
		_keyPressed = 'w';
		break;
	case sf::Keyboard::O:
		_keyPressed = 'o';
		break;
	default:
		_keyPressed = '/0';
		break;
	}
}

void Menu::setForegroundColor(sf::Color color) {
	_foregroundColor = color;
}

void Menu::setBackgroundColor(sf::Color color) {
	_backgroundColor = color;
}

sf::Color Menu::getForegroundColor() const {
	return _foregroundColor;
}

sf::Color Menu::getBackgroundColor() const {
	return _backgroundColor;
}

bool Menu::mouseOnColors(sf::Vector2f mousePos) const
{
	if (mousePos.x < colors_size_x && mousePos.y < colors_size_y) return true;
	else return false;
}

bool Menu::mouseOnWorkspace(sf::Vector2f mousePos) const
{
	if (mousePos.x > 2 && mousePos.x < 798 && mousePos.y > 62 &&  mousePos.y < 598) return true;
	else return false;
}

sf::Color Menu::takeColor(sf::Vector2f mousePos)
{
	return sf::Color(colors_pixels[static_cast<int>(4 * (mousePos.y * colors_size_x + mousePos.x) + 0)],
		colors_pixels[static_cast<int>(4 * (mousePos.y * colors_size_x + mousePos.x) + 1)],
		colors_pixels[static_cast<int>(4 * (mousePos.y * colors_size_x + mousePos.x) + 2)]);
}