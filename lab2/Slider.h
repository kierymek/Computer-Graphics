#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Slider : public sf::Drawable, public sf::Transformable 
{
public:
	Slider(const int& x, const int& y, const float& starting_parameter = 0.5);
	~Slider();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updatePosition(const sf::Vector2f& position);
	float get_parameter() const;

private:
	sf::Texture * _texture;
	sf::Sprite * _sprite;
	int size_x, size_y;
	sf::VertexArray _line;
	float _parameter;
	sf::RectangleShape *_rectangle;
};