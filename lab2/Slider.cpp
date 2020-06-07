#include "Slider.h"


Slider::Slider(const int& x, const int& y, const float& starting_parameter) : _texture(new sf::Texture()), _sprite(new sf::Sprite()), size_x(x), size_y(y), _line(sf::Lines, 2), _parameter(starting_parameter)
{	
	//tabela pikseli o zadanych wymiarach
	sf::Uint8 * colors = new sf::Uint8[4 * size_x*size_y];

	//kszta³t prostokata z czarnym obramowaniem
	_rectangle = new sf::RectangleShape(sf::Vector2f(40, 300));
	_rectangle->setOutlineColor(sf::Color::Black);
	_rectangle->setOutlineThickness(1.0f);
	_rectangle->setPosition(670, 70);

	//wypelnienie tabeli pikseli kolorami
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			if (i == 0 || y == 0 || i == size_x - 1 || j == size_y - 1) {
				colors[4 * (j * size_x + i) + 0] = 255;
				colors[4 * (j * size_x + i) + 1] = 255;
				colors[4 * (j * size_x + i) + 2] = 255;
				colors[4 * (j * size_x + i) + 3] = 255;
			}
			else
			{
				colors[4 * (j * size_x + i) + 0] = j * 255 / size_y;
				colors[4 * (j * size_x + i) + 1] = j * 255 / size_y;
				colors[4 * (j * size_x + i) + 2] = j * 255 / size_y;
				colors[4 * (j * size_x + i) + 3] = 255;
			}
		}
	}
	//stworzenie tekstury o danych wymiarach i zaktualizowanie ja tabela pikseli kolorow
	_texture->create(size_x, size_y);
	_texture->update(colors);

	//znacznik suwaka
	_line[0] = sf::Vertex(sf::Vector2f(660, 220), sf::Color::Black);
	_line[1] = sf::Vertex(sf::Vector2f(720, 220), sf::Color::Black);

	_sprite->setTexture(*_texture);
	_sprite->setPosition(670, 70);

	delete colors;
}


Slider::~Slider() {
}

//rysowanie suwaka
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(*_rectangle, states);
	target.draw(*_sprite, states);
	target.draw(_line, states);
}

//przesuwanie znacznika suwaka
void Slider::updatePosition(const sf::Vector2f& position) {
	sf::Vector2f sliderPosition = _sprite->getPosition();
	if (sliderPosition.x <= position.x && sliderPosition.x + size_x >= position.x && sliderPosition.y <= position.y && sliderPosition.y + size_y >= position.y)
	{
		_line[0].position.y = _line[1].position.y = position.y;
		_parameter = (position.y - sliderPosition.y) / static_cast<double>(size_y);
	}
}

float Slider::get_parameter() const {
	return _parameter;
}