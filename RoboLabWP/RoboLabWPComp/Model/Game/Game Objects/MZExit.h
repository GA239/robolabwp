#pragma once

//
//  MZExit.h
//  Robo Lab
//
//
#include "Model\Basic Types\MZPosition.h";

class MZExit
{
public:
	MZExit(MZPosition * position);
	virtual ~MZExit(void);

	MZPosition * position();

private:
	MZPosition * _position;
};

