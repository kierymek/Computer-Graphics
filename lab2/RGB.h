#pragma once
#include "Model.h"

class RGB : public Model
{
public:

	RGB();
	~RGB() = default;
	sf::Color modify_color(const float& radius, const float& alfa);
	void modify(const float& new_parameter);
};

