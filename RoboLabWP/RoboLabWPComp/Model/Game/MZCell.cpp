#include "pch.h"
#include "MZCell.h"


MZCell::MZCell(void)
{
	_walls = 0;
}

MZCell::MZCell(MZByte walls)
{
	_walls = walls;
}

MZCell::~MZCell(void)
{
}

void MZCell::setWallsValue(MZByte walls)
{
	_walls = walls;
}

bool MZCell::hasWallAtDirection(MZDirection direction)
{
	return _walls & (1 << direction);
}

MZByte MZCell::wallsValue(void)
{
	return _walls;
}
