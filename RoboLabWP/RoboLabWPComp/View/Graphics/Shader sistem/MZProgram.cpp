#include "pch.h"
#include "MZProgram.h"

#include "Shaders\colorShader.h"
#include "Shaders\particleShader.h"
#include "Shaders\textureShader.h"


MZProgram::MZProgram(string name)
{
	_name = name;
	_handle = glCreateProgram();
	initWithName();
}

void MZProgram::initWithName()
{
	if (_name == "texture")
	{
		glProgramBinaryOES(_handle, GL_PROGRAM_BINARY_ANGLE, gTextureProgram, sizeof(gTextureProgram));
	}
	if (_name == "color")
	{
		glProgramBinaryOES(_handle, GL_PROGRAM_BINARY_ANGLE, gColorProgram, sizeof(gColorProgram));
	}
	if (_name == "particle")
	{
		glProgramBinaryOES(_handle, GL_PROGRAM_BINARY_ANGLE, gParticleProgram, sizeof(gParticleProgram));
	}
}

MZProgram::~MZProgram(void)
{
}

void MZProgram::use()
{
	glUseProgram(_handle);
}

GLuint MZProgram::handle()
{
    return _handle;
}

string MZProgram::name()
{
	return _name;
}
