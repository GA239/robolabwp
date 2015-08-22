#include "pch.h"
#include "MZOneWayWallGraphicObject.h"

#include "Model\Game\MZGame.h"
#include "Model\Game\Game objects\MZOneWayWall.h"


#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"


void MZOneWayWallGraphicObject::render()
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
			if (objectList[i]->info() == ONEWAYWALL)
			{
				MZOneWayWall *oneWayWall = (MZOneWayWall*)objectList[i];
				MZPosition *thisPosition = oneWayWall->position();

				MatrixSystem->translate(thisPosition->x(), thisPosition->y(), 0);
				MatrixSystem->prepare();
				TextureSystem->useColorWithKey("one-way-wall");
				AnimationSystem->setWallAlphaValues(thisPosition->x(), thisPosition->y(), oneWayWall->direction());
				switch (oneWayWall->direction())
				{
					case LEFT:
						glDrawArrays(GL_LINES, 0, 2);
						break;
					case DOWN:
						glDrawArrays(GL_LINES, 3, 2);
						break;
					case RIGHT:
						MatrixSystem->translate(1, 0, 0);
						MatrixSystem->prepare();
						glDrawArrays(GL_LINES, 0, 2);
						MatrixSystem->pop();
						break;
					case UP:
						MatrixSystem->translate(0, 1, 0);
						MatrixSystem->prepare();
						glDrawArrays(GL_LINES, 3, 2);
						MatrixSystem->pop();
						break;
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