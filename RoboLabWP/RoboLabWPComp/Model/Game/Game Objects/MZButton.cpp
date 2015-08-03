#include "pch.h"
#include "MZButton.h"


MZButton::MZButton(MZPosition * position, MZDirection direction, MZTarget* target)
{
	_position = new MZPosition(*position);
    _direction = direction;
    _target = target;
	_isActivated = false;
}


MZButton::~MZButton(void)
{
	if(_position != NULL)
	{
		delete(_position);
		_position = NULL;
	}
}


MZPosition* MZButton::position()
{
	return _position;
}
MZDirection MZButton::direction()
{
	return _direction;
}
bool MZButton::isActivated()
{
	return _isActivated;
}
void MZButton::activate()
{
	if(!_isActivated)
	{
		_target->toggle();
	}
	_isActivated = true;
}
