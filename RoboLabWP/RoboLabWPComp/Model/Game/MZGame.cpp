#include "pch.h"
#include "MZGame.h"


MZGame::MZGame(void)
{
	_maze = new MZMaze();
	_currentPosition = _maze->startingPosition();
	_visitsMatrix = new MZVisitsMatrix(_maze->width() +1,_maze->height() + 1);
    _stepsCount = 0;
    visitPosition(_currentPosition);
    _isPaused = false;
    _isEnded = false;
	_minimalSteps = _maze->minimalSteps();
}


MZGame::~MZGame(void)
{
	if (_maze != NULL)
	{
		delete(_maze);
		_maze = NULL;
	}
	if (_visitsMatrix != NULL)
	{
		delete(_visitsMatrix);
		_visitsMatrix = NULL;
	}
	if (_currentPosition != NULL)
	{
		delete(_currentPosition);
		_currentPosition = NULL;
	}
}

MZMotion* MZGame::updateWithFrame( int frame)
{
    vector<MZGameObject*> _objectList = _maze->objectList();
    MZMotion *result = NULL;
    /*for (MZFlow *flow in objectList)
    {
        if(![flow isMemberOfClass: [MZFlow class]])
            continue;
        result = [flow moveInFlowWithPosition:_currentPosition andFrame:frame];
    }*/
	for (unsigned int i = 0; i < _objectList.size(); i++)
	{
		if (_objectList[i] != NULL)
		{
			if (_objectList[i]->info() == FLOW)
			{
				MZFlow *flow = (MZFlow*)_objectList[i];
				result = flow->moveInFlowWithPositionandFrame(_currentPosition, frame);
			}
		}
	}
    return result;
}
int MZGame::stepsCount()
{
    return _stepsCount;
}
int MZGame::minimalSteps()
{
    return _minimalSteps;
}

MZMoveResultCode MZGame::makeStepTo(MZDirection direction)
{
    if(_isPaused)
        return GAME_PAUSED;
    
    vector<MZGameObject*> _objectList = _maze->objectList();
	for (unsigned int i = 0; i < _objectList.size(); i++)
    {
		if (_objectList[i] != NULL)
		{
			if (_objectList[i]->info() == FLOW)
			{
				MZFlow *flow = (MZFlow *)_objectList[i];
				if(flow->isInFlow(_currentPosition))
				{
					if(direction == flow->direction() || direction == ((flow->direction() + 2) % 4))
						return MOTION_IMPOSSIBLE;
				}
			}
        }
		if (_objectList[i] != NULL)
		{
			if (_objectList[i]->info() == ONEWAYWALL)
			{
				MZOneWayWall *oneWayWall = (MZOneWayWall *)_objectList[i];
				if((oneWayWall->position()->x() == _currentPosition->x()) &&
				   (oneWayWall->position()->y() == _currentPosition->y()) &&
				   (oneWayWall->direction() == direction))
					return MOTION_IMPOSSIBLE;
			}
        }
		if (_objectList[i] != NULL)
		{
			if (_objectList[i]->info() == BUTTON)
			{
				MZButton *button = (MZButton *)_objectList[i];
				if((button->position()->x() == _currentPosition->x()) &&
				   (button->position()->y() == _currentPosition->y()) &&
				   (button->direction() == direction))
				{
					button->activate();
					return MZMoveResultCode(MOTION_IMPOSSIBLE | NEEDS_UPDATE); // не уверен
				}
			}
        }
		if (_objectList[i] != NULL)
		{
			if (_objectList[i]->info() == ROTATINGCELL)
			{
				MZRotatingCell *rotatingCell = (MZRotatingCell *)_objectList[i];
				if((rotatingCell->position()->x() == _currentPosition->x()) &&
				   (rotatingCell->position()->y() == _currentPosition->y()) &&
				   (rotatingCell->hasWallAtDirection(direction)))
				{
					return MOTION_IMPOSSIBLE;
				}
			}
        }
    }
    
	if(!_maze->cells()->cellAtPosition(_currentPosition)->hasWallAtDirection(direction))
    {
        _stepsCount++;
        _currentPosition->move(direction);
	    visitPosition(_currentPosition);
        MZPosition *exitPosition;
		for (unsigned int i = 0; i < _objectList.size(); i++)
		{
			if (_objectList[i] != NULL)
			{
				if (_objectList[i]->info() == EXIT)
				{
					MZExit* exit = (MZExit*)_objectList[i];
					exitPosition = exit ->position();
					break;
				}
			}
		}
        if((_currentPosition->x() == exitPosition->x()) && (_currentPosition->y() == exitPosition->y()))
        {
            _isEnded = true;
            return GAME_ENDED;
        }
        else
            return MOTION_PERFORMED;
    }
    return MOTION_IMPOSSIBLE;
}
void MZGame::pause()
{
    _isPaused = true;
}
void MZGame::resume()
{
    _isPaused = false;
}
bool MZGame::isPaused()
{
    return _isPaused;
}
bool MZGame::isEnded()
{
    return _isEnded;
}
void MZGame::visitPosition(MZPosition* position)
{
    _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, position);
    MZCellMatrix *cellMatrix = _maze->cells();
	MZPosition* iteratorPosition = position->copy(); //позиция некоторого абстрактного объекта, которым мы ходим по лабиринту во все стороны по прямой от текущего положения.
    
	while (iteratorPosition->x() > 0)
    {
        if(cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(LEFT))
            break;
        iteratorPosition->move(LEFT);
        _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
    }
	delete(iteratorPosition);
	iteratorPosition = position->copy();
    while (iteratorPosition->y() > 0)
    {
        if(cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(DOWN))
            break;
       iteratorPosition->move(DOWN);
        _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
    }
	delete(iteratorPosition);
    iteratorPosition = position->copy();
	while (iteratorPosition->x() < _maze->width() -1 )
    {
		if(cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(RIGHT))
            break;
		iteratorPosition->move(RIGHT);
        _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
    }
	delete(iteratorPosition);
    iteratorPosition = position->copy();
	while (iteratorPosition->y() < _maze->height() -1 )
    {
		if(cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(UP))
            break;
		iteratorPosition->move(UP);
        _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
    }
    delete(iteratorPosition);
	///

    if((!cellMatrix->cellAtPosition(position)->hasWallAtDirection(LEFT)) &&
       (!cellMatrix->cellAtPosition(position)->hasWallAtDirection(DOWN)))
    {
		iteratorPosition = position->copy();
        iteratorPosition->move(LEFT);
        iteratorPosition->move(DOWN);
        while(iteratorPosition->x() >= 0)
        {
            if( (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(RIGHT)) || 
                (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(UP)))
                break;
            MZPosition *tempPosition = iteratorPosition->copy();
            while (iteratorPosition->y() >= 0)
            {
                if((cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(RIGHT)) ||
                   (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(UP)))
                    break;
                _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
                iteratorPosition->move(DOWN);
            }
			delete(iteratorPosition);
            iteratorPosition = tempPosition->copy();
			delete(tempPosition);
			iteratorPosition->move(LEFT);
			delete(iteratorPosition);
        }
    }

    if((!cellMatrix->cellAtPosition(position)->hasWallAtDirection(LEFT)) &&
       (!cellMatrix->cellAtPosition(position)->hasWallAtDirection(UP)))
    {
		iteratorPosition = position->copy();
        iteratorPosition->move(LEFT);
        iteratorPosition->move(UP);
        while(iteratorPosition->x() >= 0)
        {
            if( (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(RIGHT)) || 
                (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(DOWN)))
                break;
            MZPosition *tempPosition = iteratorPosition->copy();
            while (iteratorPosition->y() >= 0)
            {
                if((cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(RIGHT)) ||
                   (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(DOWN)))
                    break;
                _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
                iteratorPosition->move(UP);
            }
			delete(iteratorPosition);
            iteratorPosition = tempPosition->copy();
			delete(tempPosition);
			iteratorPosition->move(LEFT);
			delete(iteratorPosition);
        }
    }

    if((!cellMatrix->cellAtPosition(position)->hasWallAtDirection(RIGHT)) &&
       (!cellMatrix->cellAtPosition(position)->hasWallAtDirection(DOWN)))
    {
		iteratorPosition = position->copy();
        iteratorPosition->move(RIGHT);
        iteratorPosition->move(DOWN);
        while(iteratorPosition->x() >= 0)
        {
            if( (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(LEFT)) || 
                (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(UP)))
                break;
            MZPosition *tempPosition = iteratorPosition->copy();
            while (iteratorPosition->y() >= 0)
            {
                if((cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(LEFT)) ||
                   (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(UP)))
                    break;
                _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
                iteratorPosition->move(DOWN);
            }
			delete(iteratorPosition);
            iteratorPosition = tempPosition->copy();
			delete(tempPosition);
			iteratorPosition->move(RIGHT);
			delete(iteratorPosition);
        }
    }
 
    if((!cellMatrix->cellAtPosition(position)->hasWallAtDirection(RIGHT)) &&
       (!cellMatrix->cellAtPosition(position)->hasWallAtDirection(UP)))
    {
		iteratorPosition = position->copy();
        iteratorPosition->move(RIGHT);
        iteratorPosition->move(UP);
        while(iteratorPosition->x() >= 0)
        {
            if( (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(LEFT)) || 
                (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(DOWN)))
                break;
            MZPosition *tempPosition = iteratorPosition->copy();
            while (iteratorPosition->y() >= 0)
            {
                if((cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(LEFT)) ||
                   (cellMatrix->cellAtPosition(iteratorPosition)->hasWallAtDirection(DOWN)))
                    break;
                _visitsMatrix->setLastVisitAtStepAtPosition(_stepsCount, iteratorPosition);
                iteratorPosition->move(UP);
            }
			delete(iteratorPosition);
            iteratorPosition = tempPosition->copy();
			delete(tempPosition);
			iteratorPosition->move(RIGHT);
			delete(iteratorPosition);
        }
    }
}