#include "pch.h"
#include "MZCellsGraphicObject.h"

#include "Model/Game/MZGame.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"


MZCellsGraphicObject::MZCellsGraphicObject(void)
{
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////

	_width = Game->_maze->width();
    _height = Game->_maze->height();
    _cellMatrix = Game->_maze->cells();

	//////////////////////////////////////////////////////////////////////
	Game->FreeInst();
}

MZCellsGraphicObject::~MZCellsGraphicObject(void)
{
}


void MZCellsGraphicObject::render()
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
                TextureSystem->useColorWithKey("cell");
                AnimationSystem->setCellAlphaValues(i, j);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                MatrixSystem->pop();
            }
			delete(thisPosition);
        }
    }
	//////////////////////////////////////////////////////////////////////
	ShaderSystem->FreeInst();
	MatrixSystem->FreeInst();
	TextureSystem->FreeInst();
	AnimationSystem->FreeInst();
	Game->FreeInst();
}
void MZCellsGraphicObject::newGame()
{
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////

	_width = Game->_maze->width();
    _height = Game->_maze->height();
    _cellMatrix = Game->_maze->cells();

	//////////////////////////////////////////////////////////////////////
	Game->FreeInst();
}
