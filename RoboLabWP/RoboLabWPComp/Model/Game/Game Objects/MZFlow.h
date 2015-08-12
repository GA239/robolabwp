#pragma once

//
//  MZFlow.h
//  Robo Lab
//
//

#include "Model\Basic Types\MZPosition.h"
#include "Model\Basic Types\MZDirection.h"
#include "Model\Basic Types\MZMotion.h"
#include "Model\Game\Game Objects\MZTarget.h"

class MZFlow :
	public MZTarget
{
public:
	MZFlow(MZPosition* pos, MZDirection dir, int length, double speed);
	virtual ~MZFlow(void);

	
	MZPosition* position();
	MZDirection direction();
	int length();
	double speed();
	MZMotion* moveInFlowWithPositionandFrame(MZPosition* position, int frame);
	bool isInFlow(MZPosition *position);
	double shift();
	void toggle();
	MZGameObjectName info() {return FLOW;}

private:

	MZDirection _direction;
    MZPosition * _position;
    int _length;
    double _speed;
	bool _isInUse;
    int _frameUpdated;
    double _shift;
};

