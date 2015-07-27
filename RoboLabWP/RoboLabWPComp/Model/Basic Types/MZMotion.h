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
	MZMotion(MZMotion &obj);
	~MZMotion(void);

	void  use(void);
	int timesUsed();

	double _speed;
	MZDirection _direction;

private:
	int _timesUsed;
};

