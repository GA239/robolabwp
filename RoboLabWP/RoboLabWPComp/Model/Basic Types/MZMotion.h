#pragma once

//
//  MZMotion.h
//  Robo Lab
//

#include "MZDirection.h"

class MZMotion
{
public:
	MZMotion(double speed, MZDirection direction);
	~MZMotion(void);

	double _speed;
	MZDirection _direction;

	void  use(void);
	int timesUsed();

private:
	int _timesUsed;
};

