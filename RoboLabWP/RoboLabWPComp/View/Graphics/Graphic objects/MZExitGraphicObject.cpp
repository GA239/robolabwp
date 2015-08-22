#include "pch.h"
#include "MZExitGraphicObject.h"

#include "Model/Game/MZGame.h"
#include "Model/Basic Types/MZMacro.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"


MZExitGraphicObject::MZExitGraphicObject(void)
{
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////

	vector<MZGameObject*> objectList = Game->_maze->objectList();
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] != NULL)
		{
			if (objectList[i]->info() == EXIT)
			{
				_exit = (MZExit*)objectList[i];
				break;
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////////
	Game->FreeInst();
}


MZExitGraphicObject::~MZExitGraphicObject(void)
{
}

void MZExitGraphicObject::render()
{
	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	MZMatrixSystem* MatrixSystem = MZMatrixSystem::getInstance();
	MZTextureSystem* TextureSystem = MZTextureSystem::getInstance();
	MZAnimationSystem* AnimationSystem = MZAnimationSystem::getInstance();
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////

    ShaderSystem->useProgramWithName("texture");
    AnimationSystem->setCellAlphaValues(_exit->position()->x(), _exit->position()->y());
    TextureSystem->useTextureWithKey("win");
    MatrixSystem->translate(_exit->position()->x(), _exit->position()->y(), 0);
    MatrixSystem->prepare();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    MatrixSystem->pop();

	//////////////////////////////////////////////////////////////////////
	ShaderSystem->FreeInst();
	MatrixSystem->FreeInst();
	TextureSystem->FreeInst();
	AnimationSystem->FreeInst();
	Game->FreeInst();
}
void MZExitGraphicObject::newGame()
{
	MZGame* Game = MZGame::getInstance();
	//////////////////////////////////////////////////////////////////////
	//vector<MZGameObject*> objectList = Game->_maze->objectList();
	//_exit = (MZExit*)objectList[0];
	_exit = (MZExit*)Game->_maze->objectList()[0];
	//////////////////////////////////////////////////////////////////////
	Game->FreeInst();
}