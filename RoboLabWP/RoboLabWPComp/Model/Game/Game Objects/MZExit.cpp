#include "pch.h"
#include "MZExit.h"


MZExit::MZExit(MZPosition * position)
{
	_position = position;
}


MZExit::~MZExit(void)
{
}


MZPosition* MZExit::position()
{
	return _position;
}