#pragma once

//
//  MZOneWayWall.h
//  Robo Lab
//

#include "Model\Basic Types\MZPosition.h";
#include "Model\Game\Game Objects\MZTarget.h";


class MZOneWayWall :
	public MZTarget
{
public:
	MZOneWayWall(MZPosition * position, MZDirection direction);
	virtual ~MZOneWayWall(void);

	
	MZPosition* position();
	MZDirection direction();
	void toggle();

private:

	MZDirection _direction;
    MZPosition * _position;
};

