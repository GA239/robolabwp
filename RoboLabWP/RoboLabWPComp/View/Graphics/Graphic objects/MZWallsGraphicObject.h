#pragma once

#include "mzgraphicobject.h"
#include "Model/Game/MZCellMatrix.h"

class MZWallsGraphicObject :
	public MZGraphicObject
{
public:
	MZWallsGraphicObject(void);
	virtual ~MZWallsGraphicObject(void);

	virtual MZGraphicObjectName info() {return GraphicWALLS;}

	virtual void update() {}
	virtual void motionUpdate() {}

	virtual void render();
	virtual void newGame();

private:
	int _width, _height;
    MZCellMatrix *_cellMatrix;
};

