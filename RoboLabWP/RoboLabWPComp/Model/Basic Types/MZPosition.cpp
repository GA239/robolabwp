#include "pch.h"
#include "MZPosition.h"


MZPosition::MZPosition(int x, int y)
{
	_x = x;
    _y = y;
}

MZPosition::MZPosition(MZPosition &objJ)
{
	_x = objJ.x();
	_y = objJ.y();
}

MZPosition::~MZPosition(void)
{
}

int MZPosition::x(void)
{
	return _x;
}

int MZPosition::y(void)
{
    return _y;
}

void MZPosition::move(MZDirection direction)
{
	switch (direction)
	{
        case LEFT:
            _x--;
            break;
        case UP:
            _y++;
            break;
        case RIGHT:
            _x++;
            break;
        case DOWN:
            _y--;
            break;
    }
}

MZPosition* MZPosition::copy(void)
{
	MZPosition* copy = new MZPosition(x(),y());
	return copy;
}

bool MZPosition::equals(MZPosition *otherPosition)
{
	if((_x == otherPosition->x()) && (_y == otherPosition->y))
        return true;
    return false;
}
