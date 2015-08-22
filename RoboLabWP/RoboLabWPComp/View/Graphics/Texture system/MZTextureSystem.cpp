#include "pch.h"
#include "MZTextureSystem.h"

#include "../Shader sistem/MZShaderSystem.h"
#include <glm/gtc/type_ptr.hpp>

MZTextureSystem* MZTextureSystem::instance;
int MZTextureSystem::_refcount;


MZTextureSystem::MZTextureSystem(void)
{
	setTextureFromImage("nanobot.tga", "nano");
    setTextureFromImage("win.tga","win");
    setColorWith( 0.007813, 0.823529, 0.729411, "wall");
    setColorWith( 0.007813, 0.823529, 0.729411, "flow");
    setColorWith( 0.113725, 0.305882, 0.364705, "cell");
    setColorWith( 0.180392, 0.592156, 0.764705, "one-way-wall");
    setColorWith( 1.0, 0.0, 0.0, "button");
}


MZTextureSystem::~MZTextureSystem(void)
{
	for (unsigned int i = 0; i < _colorList.size(); i++)
	{
		if (_colorList[i] != NULL)
		{
			delete(_colorList[i]);
			_colorList[i] = NULL;
		}
	}
	for (unsigned int i = 0; i < _textureList.size(); i++)
	{
		if (_textureList[i] != NULL)
		{
			delete(_textureList[i]);
			_textureList[i] = NULL;
		}
	}
}

void MZTextureSystem::setTextureFromImage(string resourceName, string key)
{
	MyTexture* texture = new MyTexture(resourceName,key);
	_textureList.push_back(texture);
}
void MZTextureSystem::useTextureWithKey(string key)
{
	   //GLKTextureInfo * textureInfo = [_textureList objectForKey:key];
    //glBindTexture(textureInfo.target, textureInfo.name);

	MyTexture* texture = getTextureWithKey(key);
	glBindTexture(GL_TEXTURE_2D, texture->texture());
}
void MZTextureSystem::setColorWith(double r, double g, double b, string key)
{
	MZColor *color = new MZColor(r,g,b);
	color->setName(key);
    _colorList.push_back(color);
}
void MZTextureSystem::useColorWithKey(string key)
{
	vec3 color;
	color = getColorWithKey(key)->getAsVector();

	/*
	GLfloat a[3];

	a[0] = color[0];
	a[1] = color[1];
	a[2] = color[2];

	
	a[0] = color.r;
	a[1] = color.g;
	a[2] = color.b;
	*/

	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();

	ShaderSystem->setUniform3d(value_ptr(color),"rgbColor","color");
	ShaderSystem->setUniform3d(value_ptr(color),"rgbColor","particle");

	//[[MZShaderSystem getInstance] setUniform3dValue:color.v forVariable:"rgbColor" inProgram:@"color"];

	ShaderSystem->FreeInst();

    
}

MyTexture* MZTextureSystem::getTextureWithKey(string key)
{
	for (unsigned int i = 0; i < _textureList.size(); i++)
	{
		if (_textureList[i] != NULL)
		{
			if (_textureList[i]->name() == key)
			{
				return _textureList[i];
			}
		}
		else
		{
			break;
		}
	}
	return NULL;
}

MZColor* MZTextureSystem::getColorWithKey(string key)
{
	for (unsigned int i = 0; i < _colorList.size(); i++)
	{
		if (_colorList[i] != NULL)
		{
			if (_colorList[i]->name() == key)
			{
				return _colorList[i];
			}
		}
		else
		{
			break;
		}
	}
	return NULL;
}