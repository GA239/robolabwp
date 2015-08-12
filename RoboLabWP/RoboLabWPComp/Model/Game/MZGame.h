#pragma once

//#import <UIKit/UIKit.h>
//#import <GameKit/GameKit.h>
#include "MZMaze.h"
#include "MZVisitsMatrix.h"
#include "Model\Basic Types\MZPosition.h"
#include "Model\Basic Types\MZMotion.h"
#include "Model\Basic Types\MZMoveResultCode.h"

class MZGame
{
	static MZGame* currentGame;
	static int _refcount;
public:

	static MZGame* start()
    {
		currentGame = new MZGame();
		_refcount = 0;
        return currentGame;
    }
	static MZGame* getInstance()
    {
		if(!currentGame)
		{
			start();
		}
		_refcount++;
		return currentGame;
    }
	void FreeInst() { _refcount--; if(!_refcount) {delete this; currentGame = NULL;}}

	int stepsCount();
	int minimalSteps();

	MZMoveResultCode makeStepTo(MZDirection direction);
	void pause();
	void resume();
	bool isPaused();
	bool isEnded();
	MZMotion* updateWithFrame( int frame);
	void visitPosition(MZPosition* position);

	MZMaze* _maze;
	MZVisitsMatrix* _visitsMatrix;
	MZPosition* _currentPosition;

private:
	MZGame(void);
	MZGame(const MZGame& root);
    MZGame& operator=(const MZGame&);
	virtual ~MZGame(void);

	int _stepsCount;
    int _minimalSteps;
    bool _isPaused;
    bool _isEnded;

};

