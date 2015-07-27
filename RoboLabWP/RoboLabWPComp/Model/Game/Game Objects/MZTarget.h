#pragma once

//
//  MZTarget.h
//  Robo Lab
//

class MZTarget
{
public:

	MZTarget(void) {}
	virtual ~MZTarget(void) {}

	virtual void toggle() = 0;
};

