#include "pch.h"
#include "MZMatrixSystem.h"
#include "glm\gtc\matrix_transform.hpp";


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
	_matrixStackReference.push_back(glm::mat4(1.0f));
    //GLKMatrixStackTranslateWithVector3(_matrixStackReference, vector);
	glm::translate(_matrixStackReference.back(),vector);
}

void MZMatrixSystem::translate(double x, double y, double z)
{
    //GLKMatrixStackPush(_matrixStackReference);
	_matrixStackReference.push_back(glm::mat4(1.0f));
	vec3 vector = vec3(x,y,z);
    //GLKMatrixStackTranslate(_matrixStackReference, x, y, z);
	glm::translate(_matrixStackReference.back(),vector);
}
void MZMatrixSystem::scale(double x,  double y, double z)
{
	//GLKMatrixStackPush(_matrixStackReference);
	_matrixStackReference.push_back(glm::mat4(1.0f));
    //GLKMatrixStackScale(_matrixStackReference, x, y, z);
	vec3 vector = vec3(x,y,z);
	glm::scale(_matrixStackReference.back(),vector);
}
void MZMatrixSystem::pop()
{
	_matrixStackReference.pop_back();
}
void MZMatrixSystem::prepare()
{
	
   //_modelMatrix = GLKMatrixStackGetMatrix4(_matrixStackReference);
	_modelMatrix = _matrixStackReference.back();
	//GLKMatrix4 mvMatrix = GLKMatrix4Multiply(_modelMatrix, _viewMatrix);
    mat4 mvMatrix = _modelMatrix * _viewMatrix;
    mat4 mvpMatrix = _projectionMatrix * mvMatrix;
    
    //[[MZShaderSystem getInstance] setUniform4mValue:mvpMatrix.m forVariable:"modelViewProjectionMatrix" inProgram:@"all"];
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


