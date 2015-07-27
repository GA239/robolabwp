#include "pch.h"
#include "MZMotion.h"


MZMotion::MZMotion(double speed, MZDirection direction)
{
	_speed = speed;
    _direction = direction;
    _timesUsed = 0;
}

MZMotion::MZMotion(MZMotion &obj)
{
	_speed = obj._speed;
	_direction =obj._direction;
	_timesUsed = obj.timesUsed();
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