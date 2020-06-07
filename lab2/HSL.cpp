#include "HSL.h"
#define PI 3.1415


float Hue_2_RGB(float v1, float v2,float vH)             //Function Hue_2_RGB
{
	if (vH < 0) vH += 1;
	if (vH > 1) vH -= 1;
	if ((6. * vH) < 1) return (v1 + (v2 - v1) * 6. * vH);
	if ((2. * vH) < 1) return (v2);
	if ((3. * vH) < 2) return (v1 + (v2 - v1) * ((2 / 3.) - vH) * 6.);
	return (v1);
}

HSL::HSL() : Model()
{
	create();
	_sprite->setPosition(70, 60);

	_title.setString("HSL");
	_title.setPosition(70, 60);

	_text.setString("L = " + conv_to_string(_parameter, 3));
	_text.setPosition(270, 290);
}

sf::Color HSL::modify_color(const float& radius, const float& alfa)
{
	float H = alfa *180/PI/360;
	float S = radius/_radius;
	float L = _parameter;

	float R, G, B;

	//konwersja hsl/rgb
	if (S == 0)
	{

		R = L * 255;
		G = L * 255;
		B = L * 255;
	}
	else
	{
		float var_2, var_1;
		if (L < 0.5) var_2 = L * (1. + S);
		else var_2 = (L + S) - (S * L);

		var_1 = 2. * L - var_2;

		R = 255. * Hue_2_RGB(var_1, var_2, H + (1 / 3.));
		G = 255. * Hue_2_RGB(var_1, var_2, H);
		B = 255. * Hue_2_RGB(var_1, var_2, H - (1 / 3.));
	}
	return sf::Color(R, G, B);

}

void HSL::modify(const float& new_parameter)
{
	if (fabs(_parameter - new_parameter) > 0.01) {
		_parameter = new_parameter;
		_text.setString("L = " + conv_to_string(_parameter, 3));
		fill_colors();
		_texture->update(_colors);
	}
}