#include "Model.h"
#include "font.h"
#include <cmath>

//konstruktor modelowy ktory bedzie pozniej dziedziczony
Model::Model() : _radius{ 120 }, _texture { new sf::Texture }, _sprite{ new sf::Sprite }
{
	_colors = new sf::Uint8[16 * pow(_radius,2)];
}

void Model::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_title, states);
	target.draw(_text, states);
	target.draw(*_sprite, states);
}

//metoda tworzaca wszystkie potrzebne opisy i czcionki,a takze tworz¹ca teksturê
void Model::create()
{
	_font.loadFromMemory(font_data, font_data_size);

	_text.setFont(_font);
	_text.setCharacterSize(13);
	_text.setStyle(sf::Text::Regular);

	_text.setFillColor(sf::Color::Black);
	_text.setOutlineColor(sf::Color::Black);
	_text.setPosition(0, 0);

	_title.setFont(_font);
	_title.setCharacterSize(13);
	_title.setStyle(sf::Text::Regular);

	_title.setFillColor(sf::Color::Black);
	_title.setOutlineColor(sf::Color::Black);
	_title.setPosition(0, 0);

	//wymiar tekstury na wymiar srednicy, za³adowanie tekstury do sprajta
	_texture->create(2 * _radius, 2 * _radius);
	fill_colors();
	_sprite->setTexture(*_texture);
}

//wype³anianie tablicy kolorow ko³a
void Model::fill_colors()
{
	for (int i = 0; i < 2 * _radius; i++) {
		for (int j = 0; j < 2 * _radius; j++) {

			//atan2 zwraca kat w radianach z zakresu(-pi, pi) dlatego w razie potrzeby zamieniamy na dodatki
			float angle = atan2(_radius - j, i - _radius);

			if (angle < 0) angle += 2 * 3.1415;

			//odleglosc punktu od srodka
			float dist = sqrt(pow(_radius - j,2) + pow(i - _radius, 2));

			if (dist <= _radius) {
				//aktualizacja koloru liczona osobno dla kazdego odwzorowania
				sf::Color newColor = modify_color(dist, angle);
				_colors[4 * (j * 2 * _radius + i) + 0] = newColor.r;
				_colors[4 * (j * 2 * _radius + i) + 1] = newColor.g;
				_colors[4 * (j * 2 * _radius + i) + 2] = newColor.b;
				_colors[4 * (j * 2 * _radius + i) + 3] = 255;
			}
			else {
				for (int k = 0; k < 4; k++)
					_colors[4 * (j * 2 * _radius + i) + k] = 0;
			}
		}
	}
	//aktualizacja tekstury
	_texture->update(_colors);
}

Model::~Model()
{
	if(_colors) delete[] _colors;
}

