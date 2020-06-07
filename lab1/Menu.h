#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable
{
private:
	sf::Font font;
	sf::Text *text, *title;
	sf::RectangleShape *rectangle;
	
	//wskazniki wyboru koloru
	sf::RectangleShape *_drawingColorRectangle;
	sf::RectangleShape *_fillingColorRectangle;

	//kolor przypisywany kwadratom wskazywania wyboru koloru
	sf::Color _foregroundColor;
	sf::Color _backgroundColor;

	//paleta kolorow
	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
	{
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}

	//ostatnio uzywany przycisk
	char _keyPressed;

public:
	
	Menu();
	void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const
	{
		text->setPosition(x, y);
		text->setString(str);
		target.draw(*text);

		title->setString(_keyPressed);
		title->setPosition(670, 630);
		target.draw(*title);
	}

	//rozpiska menu wyboru
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
		outtextxy(target, 5, 615, L"b - wybór koloru wypełniania");
		outtextxy(target, 5, 630, L"l - rysowanie linii");

		outtextxy(target, 200, 600, L"r - rysowanie prostokąta");
		outtextxy(target, 200, 615, L"a - rysowanie wypełnionego prostokąta");
		outtextxy(target, 200, 630, L"c - rysowanie okręgu");

		outtextxy(target, 470, 600, L"w - zapis do pliku");
		outtextxy(target, 470, 615, L"o - odczyt z pliku");
		outtextxy(target, 470, 630, L"esc - wyjście");

		outtextxy(target, 650, 615, L"Aktualne:");

		target.draw(*rectangle);
		target.draw(*colors_sprite);
		_drawingColorRectangle->setFillColor(_foregroundColor);
		_fillingColorRectangle->setFillColor(_backgroundColor);

		target.draw(*_drawingColorRectangle);
		target.draw(*_fillingColorRectangle);
	}

	//funkcji wskazujace dzialania wykonywane na menu
	void keyPressed(sf::Keyboard::Key = sf::Keyboard::Key::F1);

	bool mouseOnColors(sf::Vector2f mousePos) const;

	bool mouseOnWorkspace(sf::Vector2f mousePos) const;

	sf::Color takeColor(sf::Vector2f mousePos);

	//ustawianie wybranego koloru i pobieranie go dla innych funkcji
	void setForegroundColor(sf::Color color);
	void setBackgroundColor(sf::Color color);
	sf::Color getForegroundColor() const;
	sf::Color getBackgroundColor() const;

};