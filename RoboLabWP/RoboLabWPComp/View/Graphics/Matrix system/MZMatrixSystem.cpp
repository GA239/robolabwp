#include "pch.h"
#include "MZMatrixSystem.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

MZMatrixSystem* MZMatrixSystem::instance;
int MZMatrixSystem::_refcount;

MZMatrixSystem::MZMatrixSystem(void)
{
	_viewMatrix = mat4(1.0);
	_modelMatrix = mat4(1.0);
    setProjectionWithZoom(1.0);
    //_matrixStackReference = GLKMatrixStackCreate(CFAllocatorGetDefault());
    
}


MZMatrixSystem::~MZMatrixSystem(void)
{
}

void MZMatrixSystem::translateWithVector3(vec3 vector)
{
	//GLKMatrixStackPush(_matrixStackReference);
	
	glm::mat4x4 back = glm::mat4(1.0f);
	if(_matrixStackReference.size() != 0)
		back = _matrixStackReference.back();
	back = glm::translate(back, vector);

	_matrixStackReference.push_back(back);

    //GLKMatrixStackTranslateWithVector3(_matrixStackReference, vector);
	//_matrixStackReference.back() = glm::translate(_matrixStackReference.back(),vector);
}

void MZMatrixSystem::translate(double x, double y, double z)
{
    //GLKMatrixStackPush(_matrixStackReference);
	vec3 vector = vec3(x,y,z);
    //GLKMatrixStackTranslate(_matrixStackReference, x, y, z);
	glm::mat4x4 back = glm::mat4(1.0f);
	if(_matrixStackReference.size() != 0)
		back = _matrixStackReference.back();
	back = glm::translate(back, vector);

	_matrixStackReference.push_back(back);

}
void MZMatrixSystem::scale(double x,  double y, double z)
{
	//GLKMatrixStackPush(_matrixStackReference);
    //GLKMatrixStackScale(_matrixStackReference, x, y, z);
	vec3 vector = vec3(x,y,z);
	glm::mat4x4 back = glm::mat4(1.0f);
	if(_matrixStackReference.size() != 0)
		back = _matrixStackReference.back();
	back = glm::scale(back, vector);

	_matrixStackReference.push_back(back);

}
void MZMatrixSystem::pop()
{
	_matrixStackReference.pop_back();
}
void MZMatrixSystem::prepare()
{
	
   //_modelMatrix = GLKMatrixStackGetMatrix4(_matrixStackReference);
	_modelMatrix = mat4(1.0f);


	if(_matrixStackReference.size() != 0)
		_modelMatrix = _matrixStackReference.back();
	
	
	//GLKMatrix4 mvMatrix = GLKMatrix4Multiply(_modelMatrix, _viewMatrix);
    mat4 mvMatrix = _modelMatrix * _viewMatrix;
    mat4 mvpMatrix = _projectionMatrix * mvMatrix;
	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	ShaderSystem->setUniform4m(value_ptr(mvpMatrix),"modelViewProjectionMatrix","all");
	//[[MZShaderSystem getInstance] setUniform4mValue:mvpMatrix.m forVariable:"modelViewProjectionMatrix" inProgram:@"all"];
	ShaderSystem->FreeInst();
}
void MZMatrixSystem::setProjectionWithZoom(double zoom)
{
    //CGRect screenRect = [[UIScreen mainScreen] bounds]; нужно передать размер экрана / 
    //CGFloat screenWidth = screenRect.size.width;
    //CGFloat screenHeight = screenRect.size.height;
	float screenWidth = 480;
    float screenHeight = 800; 
    /*_projectionMatrix = GLKMatrix4MakeOrtho(-zoom * (screenWidth/CELL_SIZE_IN_PIXELS) + 0.5,
                                            zoom * (screenWidth/CELL_SIZE_IN_PIXELS) + 0.5,
                                            -zoom * (screenHeight/CELL_SIZE_IN_PIXELS) + 0.5,
                                            zoom * (screenHeight/CELL_SIZE_IN_PIXELS) + 0.5,
                                            0,10.0);*/
	_projectionMatrix = glm::ortho<float>(-zoom * (screenWidth/CELL_SIZE_IN_PIXELS) + 0.5,
                                            zoom * (screenWidth/CELL_SIZE_IN_PIXELS) + 0.5,
                                            -zoom * (screenHeight/CELL_SIZE_IN_PIXELS) + 0.5,
                                            zoom * (screenHeight/CELL_SIZE_IN_PIXELS) + 0.5,
                                            0,10.0);
}


