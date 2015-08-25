#include "pch.h"
#include "MZRenderingCore.h"

#include "Model\Game\MZGame.h"
#include "Model\Basic Types\MZMacro.h"

#include "View\Graphics\Graphic objects\MZNanobotGraphicObject.h"
#include "View\Graphics\Graphic objects\MZCellsGraphicObject.h"
#include "View\Graphics\Graphic objects\MZWallsGraphicObject.h"
#include "View\Graphics\Graphic objects\MZExitGraphicObject.h"
#include "View\Graphics\Graphic objects\MZFlowGraphicObject.h"
#include "View\Graphics\Graphic objects\MZOneWayWallGraphicObject.h"
#include "View\Graphics\Graphic objects\MZButtonGraphicObject.h"
#include "View\Graphics\Graphic objects\MZRotatingCellGraphicObject.h"


MZRenderingCore::MZRenderingCore(void)
{
	glClearColor((GLclampf)0.110, (GLclampf)0.137, (GLclampf)0.16, (GLclampf)1.0);
    glLineWidth(3.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _zoom = 1.0;
    
    _shaderSystem = MZShaderSystem::startSystem();
    _matrixSystem = MZMatrixSystem::startSystem();
    _textureSystem = MZTextureSystem::startSystem();
    _animationSystem = MZAnimationSystem::startSystem();
    _vertexSystem = MZVertexSystem::startSystem();
    
    
    //_graphicObjects = [[NSMutableDictionary alloc] init];
    //[_graphicObjects setObject:[[MZNanobotGraphicObject alloc] init] forKey:@"nanobot"];
    
	_graphicObjects.push_back(new MZNanobotGraphicObject());
    
	_graphicObjects.push_back(new MZCellsGraphicObject());
    _graphicObjects.push_back(new MZWallsGraphicObject());
    _graphicObjects.push_back(new MZExitGraphicObject());
    _graphicObjects.push_back(new MZFlowGraphicObject());
    _graphicObjects.push_back(new MZOneWayWallGraphicObject());
    _graphicObjects.push_back(new MZButtonGraphicObject());
    _graphicObjects.push_back(new MZRotatingCellGraphicObject());
    
    //[_shaderSystem linkProgramWithName:@"all"];
    //[self updateNewGame];
}


MZRenderingCore::~MZRenderingCore(void)
{
	_shaderSystem->FreeInst();
	_matrixSystem->FreeInst();
    _textureSystem->FreeInst();
    _animationSystem->FreeInst();
    _vertexSystem->FreeInst();

	for (unsigned int i = 0; i < _graphicObjects.size(); i++)
	{
		if (_graphicObjects[i] != NULL)
		{
			delete(_graphicObjects[i]);
		}
		_graphicObjects[i] = NULL;
	}
}

void MZRenderingCore::update(int frame)
{
    _animationSystem->update();
    _frame = frame;
}
void MZRenderingCore::updateStepMadeWithMotion(MZMotion * motion)
{
    if(motion != NULL)
    {
        _animationSystem->addMotion(motion);
    }
}
void MZRenderingCore::updateNewGame()
{
	_animationSystem->FreeInst();
    _animationSystem = MZAnimationSystem::startSystem();

	/*
    for (NSString * key in _graphicObjects)
        [[_graphicObjects objectForKey:key] newGame];
    */
	for (unsigned int i = 0; i < _graphicObjects.size(); i++)
	{
		_graphicObjects[i]->newGame();
	}
    updateStepMadeWithMotion(NULL);
}
void MZRenderingCore::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    _shaderSystem->useProgramWithName("particle");
	_shaderSystem->setUniform1i(_frame, "currentFrame", "particle");
	_matrixSystem->translateWithVector3(_animationSystem->positionShift());

	MZNanobotGraphicObject* nano = NULL;

	for (unsigned int i = 0; i < _graphicObjects.size(); i++)
	{
		if (_graphicObjects[i]->info() == GraphicNANOBOT)
		{
			nano = (MZNanobotGraphicObject*)_graphicObjects[i];
		}
		if (_graphicObjects[i]->info() == GraphicCELLS)
		{
			_graphicObjects[i]->render();
		}
	}

	for (unsigned int i = 0; i < _graphicObjects.size(); i++)
	{
		if (_graphicObjects[i]->info() != GraphicNANOBOT)
		{
			_graphicObjects[i]->render();
		}
	}

    _matrixSystem->pop();

	nano->render();
    //[[_graphicObjects objectForKey:@"nanobot" ] render];
}

void MZRenderingCore::pinchFired()
{
    static double initialZoom = 1;
	/*
    if(gestureRecognizer.state == UIGestureRecognizerStateBegan)
    {
        initialZoom = _zoom;
        return;
    }*/
    //_zoom = initialZoom/gestureRecognizer.scale;

	// тут будем отслеживать свайпы

    if(_zoom < 0.15)
        _zoom = 0.15;
    if(_zoom > 3)
        _zoom = 3;

    _matrixSystem->setProjectionWithZoom(_zoom);
}