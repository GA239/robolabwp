#include "pch.h"
#include "MZRotatingCell.h"


MZRotatingCell::MZRotatingCell(MZPosition* position, MZCell* cell, MZRotationDirection rotationDirection)
{
	_position = new MZPosition(*position);
    _cell = cell;
    _rotationDirection = rotationDirection;
}


MZRotatingCell::~MZRotatingCell(void)
{
	if(_cell != NULL)
	{
		delete(_cell);
	}
	if(_position != NULL)
	{
		delete(_position);
		_position = NULL;
	}
}

MZPosition* MZRotatingCell::position()
{
    return _position;
}
bool MZRotatingCell::hasWallAtDirection(MZDirection direction)
{
	return _cell->hasWallAtDirection(direction);
}
MZRotationDirection MZRotatingCell::rotationDirection()
{
	return _rotationDirection;
}
void MZRotatingCell::toggle()
{
    MZCell *newValue;
    if(_rotationDirection == CLOCKWISE)
    {
		bool isDown = _cell->hasWallAtDirection(DOWN);
        MZByte walls = _cell->wallsValue;
        walls = walls << 1;
        if(isDown)
        {
            walls = walls & 1;
            walls = walls & (1 << 4);
        }
        //newValue = [[MZCell alloc] initWithWallsValue:walls];
		newValue = new MZCell(walls);
    }
    else
    {
		BOOL isLeft = _cell->hasWallAtDirection(LEFT);
        MZByte walls = _cell->wallsValue;
        walls = walls >> 1;
        if(isLeft)
            walls = walls & (1 << DOWN);
        newValue = new MZCell(walls);
    }
    _cell = newValue;
}