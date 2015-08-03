#include "pch.h"
#include "MZMaze.h"


MZMaze::MZMaze(void)
{
    //MZUserGameData *userGameData = [MZUserGameData getInstance];
    //NSMutableData * moduleData= [userGameData currentModuleData];
    //MZByte* byteArray = [moduleData mutableBytes];
    //int level = [userGameData currentLevel];
	
	MZByte* byteArray = new MZByte(100); // временно
	int level = 1;
    
	int n = byteArray[0];
    int baseOffset = 1 + n * 2 + byteArray[1 + (level - 1) * 2] * 256 + byteArray[2 + (level - 1) * 2]; //вникать не надо. В это можно просто поверить.
	MZPosition* winningPosition = NULL;
	_startingPosition = NULL;

    _width = byteArray[baseOffset];
    _height = byteArray[baseOffset + 1];

	_cellMatrix = new MZCellMatrix(_width, _height);
    _minimalStepsRequired = byteArray[baseOffset + 2] * 256 + byteArray[baseOffset + 3];
    
	for(int i = 0; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
        {
			MZPosition *thisPosition  = new MZPosition(i,j);
			MZCell *thisCell = _cellMatrix->cellAtPosition(thisPosition);
            MZByte thisCellData = byteArray[baseOffset + i*_height + j + 4];
            MZByte walls = thisCellData & LOW4BIT;
            bool isWin = thisCellData & BIT5;
            bool isStart = thisCellData & BIT6;
            bool isEmpty = thisCellData & BIT7;
			thisCell->isEmpty = isEmpty;
			thisCell->setWallsValue(walls);
            if(isWin)
            {
                winningPosition = thisPosition;
            }
            if(isStart)
            {
                _startingPosition = thisPosition;
            }
        }
    }
    
    //_objectList = [[NSMutableArray alloc] init];
    //[_objectList addObject:[[MZExit alloc] initWithPosition:winningPosition]];
	_objectList.push_back(new MZExit(winningPosition));
	delete(winningPosition);
	//string currentmodule = "Reciever";
	int currentModuleNumber = 2;
	MZPosition *pos;
	//if([[userGameData currentModuleName] isEqualToString: @"Reciever"] && level == 1)
    if(currentModuleNumber == 2 && level == 2)
    {
        //MZFlow *flow = [[MZFlow alloc] initWithPosition: [[MZPosition alloc] initWithX:4 andY:8] direction: RIGHT length:6 andSpeed: 1.0/15.0];
		pos = new MZPosition(4,8);
		MZFlow *flow = new MZFlow(pos, RIGHT, 6, 1.0/15.0);
		delete(pos);
        //[_objectList addObject:flow];
        //[_objectList addObject:[[MZButton alloc] initWithPosition: [[MZPosition alloc] initWithX:10 andY:7] andDirection:DOWN andTarget:flow]];
		_objectList.push_back(flow);
		pos = new MZPosition(10,7);
		_objectList.push_back(new MZButton(pos, DOWN, flow));
		delete(pos);
    }
    if(currentModuleNumber == 2 && level == 1)
    {
        //[_objectList addObject:[[MZOneWayWall alloc] initWithPosition:[[MZPosition alloc] initWithX:8 andY: 5] andDirection:LEFT]];
		pos = new MZPosition(8,5);
		_objectList.push_back(new MZOneWayWall(pos, LEFT));
		delete(pos);
    }
    if(currentModuleNumber == 2 && level == 3)
    {
		MZCell* cell = new MZCell((MZByte)1);
		pos = new MZPosition(2,12);
        //MZRotatingCell* rotatingCell = [[MZRotatingCell alloc] initWithPosition:[[MZPosition alloc] initWithX:2 andY:12] andWalls:cell andRotationDirection:CLOCKWISE];
		MZRotatingCell* rotatingCell = new MZRotatingCell(pos, cell, CLOCKWISE);
		delete(pos);
        //[_objectList addObject:rotatingCell];
		_objectList.push_back(rotatingCell);
        //[_objectList addObject:[[MZButton alloc] initWithPosition:[[MZPosition alloc] initWithX:0 andY:12] andDirection:UP andTarget:rotatingCell]];
		pos = new MZPosition(0,12);
		_objectList.push_back(new MZButton(pos, UP, rotatingCell));
		delete(pos);
    }
}


MZMaze::~MZMaze(void)
{
	if(_cellMatrix != NULL)
	{
		delete(_cellMatrix);
		_cellMatrix = NULL;
	}
	if(_startingPosition != NULL)
	{
		delete(_startingPosition);
		_startingPosition = NULL;
	}
	for (unsigned int i = 0; i < _objectList.size(); i++)
	{
		if (_objectList[i] != NULL)
		{
			delete(_objectList[i]);
			_objectList[i] = NULL;
		}
	}
}

MZPosition* MZMaze::startingPosition()
{
    return _startingPosition;
}
MZCellMatrix* MZMaze::cells()
{
    return _cellMatrix;
}
vector<MZGameObject*> MZMaze::objectList()
{
	return _objectList;
}
int MZMaze::width()
{
    return _width;
}
int MZMaze::height()
{
    return _height;		
}
int MZMaze::minimalSteps()
{
    return _minimalStepsRequired;
}
