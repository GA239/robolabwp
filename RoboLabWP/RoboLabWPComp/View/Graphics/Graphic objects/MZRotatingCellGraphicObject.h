#pragma once
#include "mzgraphicobject.h"

class MZRotatingCellGraphicObject :
	public MZGraphicObject
{
public:
	MZRotatingCellGraphicObject(void);
	virtual ~MZRotatingCellGraphicObject(void);

	virtual MZGraphicObjectName info() {return GraphicROTATINGCELL;}

	virtual void update() {}
	virtual void motionUpdate() {}

	virtual void render();
	virtual void newGame() {}
};