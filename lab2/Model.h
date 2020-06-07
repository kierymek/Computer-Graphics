#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>

//klasa modelowa kola po ktorej kazde z odwzorowan bedzie dziedziczyc
class Model : public sf::Drawable, public sf::Transformable
{

public:
	Model();
	~Model();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void create();
	void fill_colors();
	virtual sf::Color modify_color(const float& radius, const float& alfa) = 0;

protected:

	sf::Texture * _texture;
	sf::Sprite * _sprite;
	sf::Font _font;
	sf::Text _title;
	sf::Text _text;
	sf::Uint8 * _colors;

	float _parameter;
	const int _radius = 100;
};


//szablon sluzacy do wypisywania zmieniajacych sie wartosci
template <typename T>
std::string conv_to_string(const T a_value, const int n = 2)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}