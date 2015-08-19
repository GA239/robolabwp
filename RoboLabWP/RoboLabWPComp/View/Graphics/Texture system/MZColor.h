//
//  MZColor.h
//  Robo Lab
//
#pragma once

#include "glm\glm.hpp"
#include <string>

using namespace std;
using namespace glm;

class MZColor
{
public:
	MZColor(vec3 color);
	MZColor(double r, double g, double b);
	virtual ~MZColor(void);

	vec3 getAsVector();

	void setName(string name);
	string name();

private:
	vec3 _color;
	string _name;

};

