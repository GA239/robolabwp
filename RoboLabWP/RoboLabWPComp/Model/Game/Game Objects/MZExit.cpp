#include "pch.h"
#include "MZExit.h"


MZExit::MZExit(MZPosition * position)
{
	_position = new MZPosition(*position);
}


MZExit::~MZExit(void)
{
	if(_position != NULL)
	{
		delete(_position);
		_position = NULL;
	}
}


MZPosition* MZExit::position()
{
	return _position;
}