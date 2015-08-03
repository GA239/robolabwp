#include "pch.h"
#include "MZVisitsMatrix.h"


MZVisitsMatrix::MZVisitsMatrix(int width, int height)
{
	_width = width;
	_height = height;
	_visits.resize(width);
	for (int i = 0; i < _width; i++)
	{
		_visits[i].resize(height);
		for (int j = 0; j < _height; j++)
		{
			_visits[i][j] = -LAST_STEPS_VISIBLE;
		}
	}
}


MZVisitsMatrix::~MZVisitsMatrix(void)
{
}


int MZVisitsMatrix::lastVisitAtPosition(MZPosition* position)
{
	if((position->x() >= 0 ) && (position->y() >=0) && (position->x() < _width) && (position->y() < _height))
    {
        return _visits[position->x()][position->y()];
    }
    return -LAST_STEPS_VISIBLE;

}

double MAX(double a, double b)
{
	if(a >= b)
	{
		return a;
	}
	return b;
}
double MZVisitsMatrix::visibilityAtXY(int x, int y)
{
	if((x >= 0) && (y >=0) && (x < _width) && (y < _height))
    {
        int lastVisit = _visits[x][y];
		MZGame* game = MZGame::getInstance();
		double res = MAX((1.0 - (double)(game->stepsCount() - lastVisit)/(double)LAST_STEPS_VISIBLE),0.0);
		game->FreeInst();
		return res;
	}
    return -LAST_STEPS_VISIBLE;
}
void MZVisitsMatrix::setLastVisitAtStepAtPosition(int step, MZPosition *position)
{
	if((position->x() >= 0 ) && (position->y() >=0) && (position->x() < _width) && (position->y() < _height))
    {
        _visits[position->x()][position->y()] = step;
        return;
    }
}
