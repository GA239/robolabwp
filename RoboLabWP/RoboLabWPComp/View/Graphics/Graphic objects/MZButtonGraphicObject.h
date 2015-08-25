#pragma once

#include "mzgraphicobject.h"

class MZButtonGraphicObject :
	public MZGraphicObject
{
public:
	MZButtonGraphicObject(void) {}
	virtual ~MZButtonGraphicObject(void);

	virtual MZGraphicObjectName info() {return GraphicBUTTON;}

	virtual void update() {}
	virtual void motionUpdate() {}

	virtual void render();
	virtual void newGame() {}

};

