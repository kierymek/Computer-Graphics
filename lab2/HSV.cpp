#include "HSV.h"
#define PI 3.1415

HSV::HSV() : Model()
{
	create();

	_sprite->setPosition(370, 60);

	_title.setString("HSV");
	_title.setPosition(370, 60);
	std::string buffer;

	_text.setString("V = " + conv_to_string(_parameter, 3));
	_text.setPosition(550, 330);
}

sf::Color HSV::modify_color(const float& radius, const float& alfa)
{
	float H = alfa * 180 / PI / 360.;
	float S = radius / _radius;
	float V = _parameter;

	float R, G, B;
	//convertion from hsv to rgb
	if (S == 0)
	{
		 R = V * 255.;
		 G = V * 255.;
		 B = V * 255.;
	}
	else
	{
		float var_h = H * 6.;
		if (var_h == 6) var_h = 0;    //H must be < 1
		float var_i = int(var_h);         //Or ... var_i = floor( var_h )
		float var_1 = V * (1 - S);
		float var_2 = V * (1 - S * (var_h - var_i));
		float var_3 = V * (1 - S * (1 - (var_h - var_i)));

		float var_r, var_g, var_b;

		if (var_i == 0) { var_r = V; var_g = var_3; var_b = var_1; }
		else if (var_i == 1) { var_r = var_2; var_g = V; var_b = var_1; }
		else if (var_i == 2) { var_r = var_1; var_g = V; var_b = var_3; }
		else if (var_i == 3) { var_r = var_1; var_g = var_2; var_b = V; }
		else if (var_i == 4) { var_r = var_3; var_g = var_1; var_b = V; }
		else { var_r = V; var_g = var_1; var_b = var_2; }

		R = var_r * 255.;
		G = var_g * 255.;
		B = var_b * 255.;
	}
	return sf::Color(R, G, B);

}

void HSV::modify(const float& new_parameter)
{
	if (fabs(_parameter - new_parameter) > 0.01) {
		_parameter = new_parameter;
		_text.setString("V = " + conv_to_string(_parameter, 3));
		fill_colors();

		_texture->update(_colors);
	}
}
