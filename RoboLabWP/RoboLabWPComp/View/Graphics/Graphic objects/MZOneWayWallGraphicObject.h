#pragma once
#include "mzgraphicobject.h"
class MZOneWayWallGraphicObject :
	public MZGraphicObject
{
public:
	MZOneWayWallGraphicObject(void) {}
	virtual ~MZOneWayWallGraphicObject(void) {}

	virtual MZGraphicObjectName info() {return GraphicONEWAYWALL;}

	virtual void update() {}
	virtual void motionUpdate() {}

	virtual void render();
	virtual void newGame() {}

};

