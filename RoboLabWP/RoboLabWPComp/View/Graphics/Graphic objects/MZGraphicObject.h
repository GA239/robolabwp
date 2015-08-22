#pragma once

#include "Model\Basic Types\MZGraphicObjectNames.h"

class MZGraphicObject
{
public:

	MZGraphicObject(void) {}

	virtual ~MZGraphicObject(void) {}
	virtual MZGraphicObjectName info() = 0;

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void newGame() = 0;
	virtual void motionUpdate() = 0;

};

