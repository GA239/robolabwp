#include "pch.h"
#include "MZRotatingCellGraphicObject.h"


#include "Model/Game/MZGame.h"
#include "Model/Game/Game Objects/MZRotatingCell.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"


MZRotatingCellGraphicObject::MZRotatingCellGraphicObject(void)
{
}


MZRotatingCellGraphicObject::~MZRotatingCellGraphicObject(void)
{
}

void MZRotatingCellGraphicObject::render()
{
	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	MZMatrixSystem* MatrixSystem = MZMatrixSystem::getInstance();
	MZTextureSystem* TextureSystem = MZTextureSystem::getInstance();
	MZAnimationSystem* AnimationSystem = MZAnimationSystem::getInstance();
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////
    ShaderSystem->useProgramWithName("color");
	vector<MZGameObject*> objectList = Game->_maze->objectList();
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] != NULL)
		{
			if (objectList[i]->info() == ROTATINGCELL)
			{
				MZRotatingCell *rCell = (MZRotatingCell*)objectList[i];
				MZPosition *thisPosition = rCell->position();
                
				MatrixSystem->translate(thisPosition->x(), thisPosition->y(), 0);
				MatrixSystem->prepare();
				TextureSystem->useColorWithKey("wall");
                
				if(rCell->hasWallAtDirection(LEFT))
				{
					AnimationSystem->setWallAlphaValues(thisPosition->x(), thisPosition->y(), LEFT);
					glDrawArrays(GL_LINES, 0, 2);
				}
                
				if(rCell->hasWallAtDirection(DOWN))
				{
					AnimationSystem->setWallAlphaValues(thisPosition->x(), thisPosition->y(), DOWN);
					glDrawArrays(GL_LINES, 3, 2);
				}
                
				if(rCell->hasWallAtDirection(RIGHT))
				{
					AnimationSystem->setWallAlphaValues(thisPosition->x(), thisPosition->y(), RIGHT);
					MatrixSystem->translate(1, 0, 0);
					MatrixSystem->prepare();
					glDrawArrays(GL_LINES, 0, 2);
					MatrixSystem->pop();
				}
                
				if(rCell->hasWallAtDirection(UP))
				{
					AnimationSystem->setWallAlphaValues(thisPosition->x(), thisPosition->y(), LEFT);
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