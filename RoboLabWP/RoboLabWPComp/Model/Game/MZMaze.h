#pragma once
//
//  MZMaze.h
//  Maze
//
//  ����� ���������. ������ ������ � ��� ���������. �� ���������� �� ���������� ����� �������.
#include "Model\Basic Types\MZPosition.h";
#include "MZCellMatrix.h";
#include <vector>;

//#import "MZUserGameData.h"  ����� ��� ����� ����� ������� ������

#include "Model\Basic Types\MZMacro.h";

#include "Model\Game\Game Objects\MZExit.h";
#include "Model\Game\Game Objects\MZFlow.h";
#include "Model\Game\Game Objects\MZOneWayWall.h";
#include "Model\Game\Game Objects\MZButton.h";
#include "Model\Game\Game Objects\MZRotatingCell.h";


class MZMaze
{
public:
	MZMaze(void);
	virtual ~MZMaze(void);

	MZPosition* startingPosition();
	MZCellMatrix* cells();
	vector<MZGameObject*> objectList();
	int width();
	int height();
	int minimalSteps();

private:
	vector<MZGameObject*> _objectList;
    int _width;
    int _height;
    int _minimalStepsRequired;
    MZPosition *_startingPosition;
    MZCellMatrix *_cellMatrix;
};

