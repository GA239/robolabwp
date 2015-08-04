#pragma once
//
//  MZAnimationSystem.h
//  Robo Lab
//
#include "Model\Basic Types\MZMotion.h";
#include "Model\Basic Types\MZMacro.h"
#include "Model\Basic Types\MZPosition.h"
#include "Model\Game\MZGame.h"
#include "MZAlphaMap.h"
//#include "MZShaderSystem.h"
//#include <vector>;
#include "glm\glm.hpp";
using namespace glm;

class MZAnimationSystem
{
		static MZAnimationSystem* instance;
		static int _refcount;
public:

	static MZAnimationSystem* startSystem()
    {
		instance = new MZAnimationSystem();
		_refcount = 0;
        return instance;
    }
	static MZAnimationSystem* getInstance()
    {
		if(!instance)
		{
			startSystem();
		}
		_refcount++;
		return instance;
    }
	void FreeInst() { _refcount--; if(!_refcount) {delete this; instance = NULL;}}

	
	void update();
	void addMotion(MZMotion * motion);
	vec3 positionShift();


	void setCellAlphaValues(int x, int y);
	void setWallAlphaValues(int x, int y, MZDirection dir);
	void setOneAlphaValues();

private:
	MZAnimationSystem(void);
	virtual ~MZAnimationSystem(void);
	MZAnimationSystem(const MZAnimationSystem& root);
	MZAnimationSystem& operator=(const MZAnimationSystem&);

	vec3 _visibleVector;

    vector<MZMotion*> _motionList;
    //NSMutableArray *_visibleObjectsParameters;
    MZAlphaMap *_realAlphaMap;
    MZAlphaMap *_visibleAlphaMap;
    float _alphaValues[4];

};

