#pragma once
//
//  MZExit.h
//  Robo Lab
//
//
#include "Model\Basic Types\MZPosition.h"


#include "MZGameObject.h"
class MZExit :
	public MZGameObject
{
public:
	MZExit(MZPosition * position);
	virtual ~MZExit(void);

	MZPosition * position();
	MZGameObjectName info() {return EXIT;}


private:
	MZPosition * _position;

};

