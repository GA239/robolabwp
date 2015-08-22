#pragma once
#include "mzgraphicobject.h"
class MZNanobotGraphicObject :
	public MZGraphicObject
{
public:
	MZNanobotGraphicObject(void) {}
	virtual ~MZNanobotGraphicObject(void) {}

	virtual MZGraphicObjectName info() {return GraphicNANOBOT;}

	virtual void update() {}
	virtual void motionUpdate() {}

	virtual void render();
	virtual void newGame() {}
};

