#include "pch.h"
#include "MZWallsGraphicObject.h"

#include "Model/Game/MZGame.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"


MZWallsGraphicObject::MZWallsGraphicObject(void)
{
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////

    _width = Game->_maze->width();
    _height = Game->_maze->height();
    _cellMatrix = Game->_maze->cells();

	//////////////////////////////////////////////////////////////////////
	Game->FreeInst();
}


MZWallsGraphicObject::~MZWallsGraphicObject(void)
{
	if (_cellMatrix != NULL)
	{
		delete(_cellMatrix);
		_cellMatrix = NULL;
	}
}

void MZWallsGraphicObject::render()
{
	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	MZMatrixSystem* MatrixSystem = MZMatrixSystem::getInstance();
	MZTextureSystem* TextureSystem = MZTextureSystem::getInstance();
	MZAnimationSystem* AnimationSystem = MZAnimationSystem::getInstance();
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////
    ShaderSystem->useProgramWithName("color");
	for(int i = 0; i < _width; i++)
    {
        for(int j = 0; j < _height; j++)
        {
            MZPosition *thisPosition = new MZPosition(i,j);
            MZCell *thisCell = _cellMatrix->cellAtPosition(thisPosition);
            
            if(!thisCell->isEmpty)
            {

                MatrixSystem->translate(i, j, 0);
                MatrixSystem->prepare();
                TextureSystem->useColorWithKey("wall");
                
				AnimationSystem->setOneAlphaValues();
                if(thisCell->hasWallAtDirection(LEFT))
                {
                    AnimationSystem->setWallAlphaValues(i, j, LEFT);
                    glDrawArrays(GL_LINES, 0, 2);
                }
                
                if(thisCell->hasWallAtDirection(DOWN))
                {
                    AnimationSystem->setWallAlphaValues(i, j, DOWN);
                    glDrawArrays(GL_LINES, 3, 2);
                }
                
                if(thisCell->hasWallAtDirection(RIGHT))
                {
                    AnimationSystem->setWallAlphaValues(i, j, RIGHT);
                    MatrixSystem->translate(1, 0, 0);
                    MatrixSystem->prepare();
                    glDrawArrays(GL_LINES, 0, 2);
                    MatrixSystem->pop();
                }
                
                if(thisCell->hasWallAtDirection(UP))
                {
                    AnimationSystem->setWallAlphaValues(i, j, UP);
                    MatrixSystem->translate(0, 1, 0);
                    MatrixSystem->prepare();
                    glDrawArrays(GL_LINES, 3, 2);
                    MatrixSystem->pop();
                }
				
                MatrixSystem->pop();
            }
        }
    }
	//////////////////////////////////////////////////////////////////////
	ShaderSystem->FreeInst();
	MatrixSystem->FreeInst();
	TextureSystem->FreeInst();
	AnimationSystem->FreeInst();
	Game->FreeInst();
}
void MZWallsGraphicObject::newGame()
{
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////

    _width = Game->_maze->width();
    _height = Game->_maze->height();
    _cellMatrix = Game->_maze->cells();

	//////////////////////////////////////////////////////////////////////
	Game->FreeInst();
}
