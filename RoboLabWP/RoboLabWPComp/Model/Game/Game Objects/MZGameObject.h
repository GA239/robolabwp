#pragma once

#include "Model\Basic Types\MZGameObjectsNames.h";

class MZGameObject
{
public:

	MZGameObject(void) {}

	virtual ~MZGameObject(void){}
	virtual MZGameObjectName info() = 0;
};

