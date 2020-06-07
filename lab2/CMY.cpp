#include "CMY.h"
#define PI 3.1415

CMY::CMY() :  Model()
{
	create();

	_sprite->setPosition(70, 360);

	_title.setString("CMY");
	_title.setPosition(70, 360);
	std::string buffer;

	_text.setString("Y = " + conv_to_string(_parameter * 100, 0) + "%");
	_text.setPosition(270, 590);
}


sf::Color CMY::modify_color(const float& radius, const float& alfa)
{
	float M = alfa * 180 / PI / 360;
	float C = radius / _radius;
	float Y = _parameter;

	float R = (1 - C) * 255;
	float G = (1 - M) * 255;
	float B = (1 - Y) * 255;
	return sf::Color(R, G, B);
}

void CMY::modify(const float& new_parameter)
{
	if (fabs(_parameter - new_parameter) > 0.01) {
		_parameter = new_parameter;
		_text.setString("Y = " + conv_to_string(_parameter * 100, 0) + "%");
		fill_colors();
		_texture->update(_colors);
	}
}
