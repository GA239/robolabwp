#include "pch.h"
#include "MZFlow.h"


MZFlow::MZFlow(MZPosition * pos, MZDirection dir, int length, double speed)
{
	_position = new MZPosition(*pos);
    _direction = dir;
    _length = length;
    _speed = speed;
	_isInUse = false;
}

MZFlow::~MZFlow(void)
{
	if(_position != NULL)
	{
		delete(_position);
		_position = NULL;
	}
}

MZPosition* MZFlow::position()
{
	return _position;
}
MZDirection MZFlow::direction()
{
	return _direction;
}

int MZFlow::length()
{
	return _length;
}
double MZFlow::speed()
{
	return _speed;
}
MZMotion* MZFlow::moveInFlowWithPositionandFrame(MZPosition* position, int frame)
{
	if(!isInFlow(position))
    {
        _isInUse = false;
        _shift = 0;
		return NULL;
    }
    if(!_isInUse)
    {
		_isInUse = true;
        _frameUpdated = frame;
        position->move(_direction);
         _shift = 0;
		 return new MZMotion(_speed,_direction);
    }
    else
    {
        if(frame - _frameUpdated >= 1.0 / _speed)
        {
            _frameUpdated = frame;
            position->move(_direction);
            return new MZMotion(_speed,_direction);
        }
        _shift = (double)(frame - _frameUpdated) * _speed;
    }
	return NULL;
}
bool MZFlow::isInFlow(MZPosition *position)
{
	switch (_direction)
    {
        case UP:
			if(_position->x() != position->x())
                return false;
            else
            {
				if((_position->y() <= position->y()) && (position->y() < _position->y() + _length - 1))
					return true;
                else
					return false;
            }
            break;
        case RIGHT:
            if(_position->y() != position->y())
                return false;
            else
            {
                if((_position->x() <= position->x()) && (position->x() < _position->x() + _length - 1))
                    return true;
                else
                    return false;
            }
            break;
        case DOWN:
            if(_position->x() != position->x())
				return false;
            else
            {
                if((_position->y() >= position->y()) && (position->y() > _position->y() - _length + 1))
                    return true;
                else
                    return false;
            }
            break;
        case LEFT:
            if(_position->y() != position->y())
                return false;
            else
            {
                if((_position->x() >= position->x()) && (position->x() > _position->x() - _length + 1))
                    return true;
                else
                    return false;
            }
        break;
    }
	return false;
}
double MZFlow::shift()
{
	return _shift;
}
void MZFlow::toggle()
{
	int x = _position->x();
	int y = _position->y();
	if(_position != NULL)
	{
		delete(_position);
		_position = NULL;
	}
    switch (_direction)
    {
        case LEFT:
            //_position = [[MZPosition alloc] initWithX:[_position x] - _length + 1 andY:[_position y]];
			x = x - _length + 1;
            break;
        case RIGHT:
            //_position = [[MZPosition alloc] initWithX:[_position x] + _length  - 1 andY:[_position y]];
			x = x + _length - 1;
			break;
        case UP:
            //_position = [[MZPosition alloc] initWithX:[_position x] andY:[_position y] + _length - 1];
			y = y + _length - 1;
            break;
        case DOWN:
            //_position = [[MZPosition alloc] initWithX:[_position x] andY:[_position y] - _length + 1];
			y = y - _length + 1;
            break;
    }
	_position = new MZPosition(x,y);
	_direction = (MZDirection)((_direction + 2) %4);
}