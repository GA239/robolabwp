#include "pch.h"
#include "MZColor.h"


MZColor::MZColor(vec3 color)
{
	_color = color;
}

MZColor::MZColor(double r, double g, double b)
{
	_color = vec3(r, g, b);
}


MZColor::~MZColor(void)
{
}

vec3 MZColor::getAsVector()
{
    return _color;
}

void MZColor::setName(string name)
{
	_name = name;
}
string MZColor::name()
{
	return _name;
}
