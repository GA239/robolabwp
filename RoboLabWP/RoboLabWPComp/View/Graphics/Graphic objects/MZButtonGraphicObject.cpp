#include "pch.h"
#include "MZButtonGraphicObject.h"

#include "Model/Game/MZGame.h"
#include "Model/Game/Game Objects/MZButton.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"


MZButtonGraphicObject::~MZButtonGraphicObject(void)
{

}

void MZButtonGraphicObject::render()
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
			if (objectList[i]->info() == BUTTON)
			{
				MZButton *button = (MZButton*)objectList[i];
				MZPosition *thisPosition = button->position();

				MatrixSystem->translate(thisPosition->x(),thisPosition->y(),0);
				TextureSystem->useColorWithKey("button");
				AnimationSystem->setCellAlphaValues(thisPosition->x(),thisPosition->y());
				double buttonWidth = 0.3;
				switch (button->direction())
				{
					case LEFT:
						MatrixSystem->scale(buttonWidth,1.0,1.0);
						MatrixSystem->prepare();
						glDrawArrays(GL_TRIANGLES, 0, 6);
						break;
					case DOWN:
						MatrixSystem->scale(1.0,buttonWidth,1.0);
						MatrixSystem->prepare();
						glDrawArrays(GL_TRIANGLES, 0, 6);
						break;
					case RIGHT:
						MatrixSystem->translate(1 - buttonWidth, 0, 0);
						MatrixSystem->scale(buttonWidth,1.0,1.0);
						MatrixSystem->prepare();
						glDrawArrays(GL_TRIANGLES, 0, 6);
						MatrixSystem->pop();
						break;
					case UP:
						MatrixSystem->translate(0, 1 - buttonWidth, 0);
						MatrixSystem->scale(1.0,buttonWidth,1.0);
						MatrixSystem->prepare();
						glDrawArrays(GL_TRIANGLES, 0, 6);
						MatrixSystem->pop();
						break;
				}
				MatrixSystem->pop();
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
