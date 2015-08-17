//
//  MZColor.h
//  Robo Lab
//
#pragma once

#include "glm\glm.hpp"

using namespace glm;

class MZColor
{
public:
	MZColor(vec3 color);
	MZColor(double r, double g, double b);
	virtual ~MZColor(void);

	vec3 getAsVector();

private:
	vec3 _color;

};

