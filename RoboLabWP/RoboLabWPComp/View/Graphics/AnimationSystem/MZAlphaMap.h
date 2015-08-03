#pragma once
//
//  MZAlphaMap.h
//  Robo Lab
//

#include "MZCellCorners.h";
#include "Model\Game\MZGame.h"
#include "Model\Basic Types\MZMacro.h"

class MZAlphaMap
{
public:
	MZAlphaMap(void);
	virtual ~MZAlphaMap(void);

	void setReal();
	void updateToMap(MZAlphaMap* realMap);
	float valueAtXYinCorner(int x, int y, MZCellCorners corner);

private:
	int _width, _height;
    float ***_map;

};

