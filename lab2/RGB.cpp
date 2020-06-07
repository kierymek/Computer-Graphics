#include "RGB.h"
#define PI 3.1415


RGB::RGB()
{
	create();
	_sprite->setPosition(370, 360);

	_title.setString("RGB");
	_title.setPosition(370, 360);
	std::string buffer;

	_text.setString("B = " + conv_to_string(_parameter * 255, 0));
	_text.setPosition(550, 590);
}



sf::Color RGB::modify_color(const float& radius, const float& alfa)
{
	float R = radius / _radius;
	float G = alfa * 180 / PI / 360.;
	float B = _parameter;

	R *= 255;
	G *= 255;
	B *= 255;

	return sf::Color(R, G, B);
}

void RGB::modify(const float& new_parameter)
{
	if (fabs(_parameter - new_parameter) > 0.01) {
		_parameter = new_parameter;
		_text.setString("B = " + conv_to_string(_parameter * 255, 0));
		fill_colors();
		_texture->update(_colors);
	}
}