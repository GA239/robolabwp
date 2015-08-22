#include "pch.h"
#include "MZNanobotGraphicObject.h"

#include "View/Graphics/Shader sistem/MZShaderSystem.h"
#include "View/Graphics/Matrix system/MZMatrixSystem.h"
#include "View/Graphics/Texture system/MZTextureSystem.h"
#include "View/Graphics/Animation system/MZAnimationSystem.h"


void MZNanobotGraphicObject::render()
{
	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	MZMatrixSystem* MatrixSystem = MZMatrixSystem::getInstance();
	MZTextureSystem* TextureSystem = MZTextureSystem::getInstance();
	MZAnimationSystem* AnimationSystem = MZAnimationSystem::getInstance();
	//////////////////////////////////////////////////////////////////////
    ShaderSystem->useProgramWithName("texture");
    AnimationSystem->setOneAlphaValues();
    MatrixSystem->prepare();
    TextureSystem->useTextureWithKey("nano");
    glDrawArrays(GL_TRIANGLES, 0, 6);
	//////////////////////////////////////////////////////////////////////
	ShaderSystem->FreeInst();
	MatrixSystem->FreeInst();
	TextureSystem->FreeInst();
	AnimationSystem->FreeInst();
}