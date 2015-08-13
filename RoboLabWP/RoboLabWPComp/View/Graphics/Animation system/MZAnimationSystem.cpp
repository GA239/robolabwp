#include "pch.h"
#include "MZAnimationSystem.h"
#include "Model\Game\MZGame.h"

MZAnimationSystem* MZAnimationSystem::instance;
int MZAnimationSystem::_refcount;


MZAnimationSystem::MZAnimationSystem(void)
{
	MZGame *game = MZGame::getInstance();
	MZPosition *realPosition = game->_currentPosition;
	game->FreeInst();    

    //_visibleVector = GLKVector3Make([realPosition x], [realPosition y], 0);
	_visibleVector = vec3(realPosition->x(),realPosition->y(),0);

    //_motionList = [[NSMutableArray alloc] init];
	_realAlphaMap = new MZAlphaMap();
    _visibleAlphaMap = new MZAlphaMap();
	_realAlphaMap->setReal();
}


MZAnimationSystem::~MZAnimationSystem(void)
{
	delete(_realAlphaMap);
	delete(_visibleAlphaMap);
	for (unsigned int i = 0; i < _motionList.size(); i++)
	{
		if (_motionList[i] != NULL)
		{
			delete(_motionList[i]);
		}
	}
}

void MZAnimationSystem::applyAlpha()
{
	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	ShaderSystem->setUniform2m(_alphaValues,"alphaValues", "color");
	ShaderSystem->setUniform2m(_alphaValues,"alphaValues", "texture");
    //[[MZShaderSystem getInstance] setUniform2mValue:_alphaValues forVariable:"alphaValues" inProgram:@"color"];
    //[[MZShaderSystem getInstance] setUniform2mValue:_alphaValues forVariable:"alphaValues" inProgram:@"texture"];
	ShaderSystem->FreeInst();
}

void MZAnimationSystem::update()
{
	
	MZGame *game = MZGame::getInstance();
	MZPosition *realPosition = game->_currentPosition;
	game->FreeInst();

    vec3 realVector = vec3(realPosition->x(),realPosition->y(),0);

	vec3 delta = realVector - _visibleVector;
    //vec3 delta = GLKVector3Subtract(realVector, _visibleVector);

	double length = delta.length();
    if(length > MOVE_SPEED)
    {
        vec3 step = vec3(0, 0, 0);
		for (unsigned int i = 0; i < _motionList.size(); i++)
        {
            MZMotion * motion = _motionList[i];
			if(motion->timesUsed() == 0)
            {
				_realAlphaMap->setReal();
            }
			if(motion->timesUsed() >= 1.0/motion->_speed)
            {
				//[_motionList removeObject:motion];
				_motionList.erase(_motionList.begin() + i - 1);
                i--;
                continue;
            }
			motion->use();
			switch (motion->_direction)
            {
                case LEFT:
					step += vec3(-motion->_speed, 0, 0);
                    //step = GLKVector3Add(step, GLKVector3Make(-[motion speed], 0, 0));
                    break;
                case UP:
					step += vec3(0, motion->_speed, 0);
					//step = GLKVector3Add(step, GLKVector3Make(0, [motion speed], 0));
                    break;
                case RIGHT:
					step += vec3(motion->_speed, 0,0);
					//step = GLKVector3Add(step, GLKVector3Make([motion speed], 0, 0));
                    break;
                case DOWN:
					
					//vec3 tmp_1 = vec3(0,-motion->_speed,0);
					//vec3 tmp = step + tmp_1;
					//step = tmp;
					step += vec3(0,-motion->_speed,0);
                    //step = GLKVector3Add(step, GLKVector3Make(0, -[motion speed], 0));
                    break;
            }
        }
        //_visibleVector = GLKVector3Add(_visibleVector, step);
		_visibleVector += step; 
    }
    else
    {
        _visibleVector = realVector;
		_motionList.clear();
    }
    
	_visibleAlphaMap->updateToMap(_realAlphaMap);
}

void MZAnimationSystem::addMotion(MZMotion* motion)
{
	_motionList.push_back(motion);
}

vec3 MZAnimationSystem::positionShift()
{
	//return GLKVector3Negate(_visibleVector);
	vec3 result = vec3(_visibleVector);
	result *= -1;
	return result;
}


void MZAnimationSystem::setCellAlphaValues(int x, int y)
{
	_alphaValues[0] = _visibleAlphaMap->valueAtXYinCorner(x, y, BOTTOM_LEFT);
    _alphaValues[1] = _visibleAlphaMap->valueAtXYinCorner(x, y, TOP_LEFT);
    _alphaValues[2] = _visibleAlphaMap->valueAtXYinCorner(x, y, BOTTOM_RIGHT);
    _alphaValues[3] = _visibleAlphaMap->valueAtXYinCorner(x, y, TOP_RIGHT);
    applyAlpha();
}

float MAX(double x, double y)
{
	return float(x > y ? x : y);
}

void MZAnimationSystem::setWallAlphaValues(int x, int y, MZDirection dir)
{
    int width, height;
	MZGame *game = MZGame::getInstance();
	width = game->_maze->width();
    height = game->_maze->height();
	game->FreeInst();    
    switch(dir)
    {
        case LEFT:
			
			_alphaValues[0] =  MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, BOTTOM_LEFT),(x > 0 ? _visibleAlphaMap->valueAtXYinCorner(x - 1, y, BOTTOM_RIGHT) : 0));
        
            _alphaValues[1] = MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, TOP_LEFT),(x > 0 ? _visibleAlphaMap->valueAtXYinCorner(x - 1, y, TOP_RIGHT) : 0));
        
            break;
            
            
        case DOWN:
            _alphaValues[0] = MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, BOTTOM_LEFT),(y > 0 ? _visibleAlphaMap->valueAtXYinCorner(x, y - 1, TOP_LEFT) : 0));
            
            _alphaValues[2] = MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, BOTTOM_RIGHT),(y > 0 ? _visibleAlphaMap->valueAtXYinCorner(x, y - 1, TOP_RIGHT) : 0));
            
            break;
        case RIGHT:
            _alphaValues[0] = MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, BOTTOM_RIGHT),(x < width - 1 ? _visibleAlphaMap->valueAtXYinCorner(x + 1, y, BOTTOM_LEFT) : 0));
            
            _alphaValues[1] = MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, TOP_RIGHT),(x < width - 1 ? _visibleAlphaMap->valueAtXYinCorner(x + 1, y, TOP_LEFT) : 0));
            
            break;
        case UP:
            _alphaValues[0] = MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, TOP_LEFT),(y < height - 1 ? _visibleAlphaMap->valueAtXYinCorner(x, y + 1, BOTTOM_LEFT) : 0));
            
            _alphaValues[2] = MAX(_visibleAlphaMap->valueAtXYinCorner(x, y, TOP_RIGHT),(y < height - 1 ? _visibleAlphaMap->valueAtXYinCorner(x, y + 1, BOTTOM_RIGHT) : 0));
            
            break;
    }
    applyAlpha();
}
void MZAnimationSystem::setOneAlphaValues()
{
    for(int i = 0; i < 4; i++)
	{
		_alphaValues[i] = 1.0;
	}
    applyAlpha();
}

