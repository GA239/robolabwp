#include "pch.h"
#include "MZMotion.h"


MZMotion::MZMotion(double speed, MZDirection direction)
{
	_speed = speed;
    _direction = direction;
    _timesUsed = 0;
}


MZMotion::~MZMotion(void)
{
}

void MZMotion::use(void)
{
	_timesUsed++;
}

int MZMotion::timesUsed(void)
{
	return _timesUsed;
}