#pragma once
#include "mzgraphicobject.h"

class MZFlowGraphicObject :
	public MZGraphicObject
{
public:
	MZFlowGraphicObject(void);
	virtual ~MZFlowGraphicObject(void);

	virtual MZGraphicObjectName info() {return GraphicFLOW;}

	virtual void update() {}
	virtual void motionUpdate() {}

	virtual void render();
	virtual void newGame();

private:
	int _particlesCount;
    float *_particlePositionData;
    float *_particlePropertiesData;
};

