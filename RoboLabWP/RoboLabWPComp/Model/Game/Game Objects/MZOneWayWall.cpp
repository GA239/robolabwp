#include "pch.h"
#include "MZOneWayWall.h"


MZOneWayWall::MZOneWayWall(MZPosition * position, MZDirection direction)
{
	_position = new MZPosition(*position);
    _direction = direction;
}


MZOneWayWall::~MZOneWayWall(void)
{
	if(_position != NULL)
	{
		delete(_position);
		_position = NULL;
	}
}

MZPosition* MZOneWayWall::position()
{
	return _position;
}

MZDirection MZOneWayWall::direction()
{
	return _direction;
}

void MZOneWayWall::toggle()
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
            //_position = [[MZPosition alloc] initWithX:[_position x] + 1 andY:[_position y]];
			x += 1;
            break;
        case RIGHT:
            //_position = [[MZPosition alloc] initWithX:[_position x] - 1 andY:[_position y]];
			x -= 1;
			break;
        case UP:
            //_position = [[MZPosition alloc] initWithX:[_position x] andY:[_position y] + 1];
			y += 1;
            break;
        case DOWN:
            //_position = [[MZPosition alloc] initWithX:[_position x] andY:[_position y] - 1];
			y -= 1;
            break;
    }
	_position = new MZPosition(x,y);
	_direction = (MZDirection)((_direction + 2) %4);
}