#pragma once
#include "Model.h"

class HSL : public Model
{
public:

	HSL();
	~HSL() = default;
	sf::Color modify_color(const float& radius, const float& alfa);
	void modify(const float& new_parameter);
};

