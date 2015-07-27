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

MZCellMatrix::MZCellMatrix(MZCellMatrix &obj)
{
	_cells.resize(obj._cells.size());
    for(int i = 0; i < obj._cells.size(); i++)
    {
		_cells[i].resize(obj._cells[i].size());
        for(int j = 0; j < obj._cells[i].size(); j++)
        {
			_cells[i][j] = new MZCell(obj._cells[i][j]->wallsValue());
        }
    }
}

MZCellMatrix::~MZCellMatrix(void)
{
	int width = _cells.size(), int height = _cells[0].size();
	for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
			delete(_cells[i][j]);
        }
    }
}

MZCell* MZCellMatrix::cellAtPosition(MZPosition * position)
{
	if((position->x() >= 0) && (position->y() >=0) && (position->x() < _cells.size()) && (position->y() < _cells[position->x()].size()))
    {
        return _cells[position->x()][position->y()];
    }
    return new MZCell();
}