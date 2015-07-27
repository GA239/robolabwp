#include "pch.h"
#include "MZCellMatrix.h"


MZCellMatrix::MZCellMatrix(int width, int height)
{
	_cells.resize(width);
    for(int i = 0; i < width; i++)
    {
		_cells[i].resize(height);
        for(int j = 0; j < height; j++)
        {
			_cells[i][j] = new MZCell();
        }
    }
}


MZCellMatrix::~MZCellMatrix(void)
{
}

MZCell* MZCellMatrix::cellAtPosition(MZPosition * position)
{
	if((position->x() >= 0) && (position->y() >=0) && (position->x() < _cells.size()) && (position->y() < _cells[position->x()].size()))
    {
        return _cells[position->x()][position->y()];
    }
    return new MZCell();
}