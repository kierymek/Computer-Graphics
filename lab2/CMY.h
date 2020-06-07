#pragma once
#include "Model.h"

class CMY : public Model
{
public:

	CMY();
	~CMY() = default;
	sf::Color modify_color(const float& radius, const float& alfa);
	void modify(const float& new_parameter);
};

