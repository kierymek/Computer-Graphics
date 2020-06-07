#pragma once
#include "Model.h"

class HSV : public Model
{
public:

	HSV();
	~HSV() = default;
	sf::Color modify_color(const float& radius, const float& alfa);
	void modify(const float& new_parameter);
};

