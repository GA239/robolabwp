#pragma once
#include "mzgraphicobject.h"
#include "Model\Game\Game objects\MZExit.h"

class MZExitGraphicObject :
	public MZGraphicObject
{
public:
	MZExitGraphicObject(void);
	virtual ~MZExitGraphicObject(void);

	virtual MZGraphicObjectName info() {return GraphicEXIT;}

	virtual void update() {}
	virtual void motionUpdate() {}

	virtual void render();
	virtual void newGame();

private:
	MZExit *_exit;
};

