#pragma once
#include "MZGameObject.h";
class MZTarget :
	public MZGameObject
{
public:

	MZTarget(void) {}
	virtual ~MZTarget(void) {}

	virtual void toggle() = 0;
	MZGameObjectName info() {return TARGET;}

};

