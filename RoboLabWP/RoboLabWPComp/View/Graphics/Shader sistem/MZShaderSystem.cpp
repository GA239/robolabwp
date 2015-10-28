#include "pch.h"
#include "MZShaderSystem.h"

MZShaderSystem* MZShaderSystem::instance;
int MZShaderSystem::_refcount;

MZShaderSystem::MZShaderSystem(void)
{
	string str = "texture";
	MZProgram* textureProgram = new MZProgram(str);
	str = "color";
    MZProgram* colorProgram = new MZProgram(str);
    str = "particle";
	MZProgram* particleProgram = new MZProgram(str);

	_programList.push_back(textureProgram);
	_programList.push_back(colorProgram);
	_programList.push_back(particleProgram);
}

MZShaderSystem::~MZShaderSystem(void)
{
	for (unsigned int i = 0; i < _programList.size(); i++)
	{
		if (_programList[i] != NULL)
		{
			delete(_programList[i]);
			_programList[i] = NULL;
		}
	}
}

GLuint MZShaderSystem::getHandleByName(string name)
{
	for (unsigned int i = 0; i < _programList.size(); i++)
	{
		if (_programList[i]->name() == name)
		{
			return _programList[i]->handle();
		}
	}
	return _programList[0]->handle();
}
void MZShaderSystem::useProgramWithName(string name)
{
	for (unsigned int i = 0; i < _programList.size(); i++)
	{
		if (_programList[i]->name() == name)
		{
			_programList[i]->use();
			return;
		}
	}
}

void MZShaderSystem::setAttribute(GLuint attribIndex, char* varName, string name)
{
	//glBindAttribLocation([[_programList objectForKey:name] handle], attribIndex, varName);
	for (unsigned int i = 0; i < _programList.size(); i++)
	{
		if (_programList[i]->name() == name)
		{
			glBindAttribLocation(_programList[i]->handle(),attribIndex,varName);
			return;
		}
	}
}
void MZShaderSystem::setUniform1i(int value, char* varName, string name)
{
	GLuint location;
	if(name ==  "all")
    {
        for (unsigned int i = 0; i < _programList.size(); i++)
		{
			location = glGetUniformLocation(_programList[i]->handle(), varName);
            glUniform1i(location, value);
        }
    }
	else
    {
		for (unsigned int i = 0; i < _programList.size(); i++)
		{
			if (_programList[i]->name() == name)
			{
				location = glGetUniformLocation(_programList[i]->handle(), varName);
				glUniform1i(location, value);

				return;
			}
        }
    }
}
void MZShaderSystem::setUniform2m(GLfloat* value, char* varName, string name)
{
	GLuint location;
	if(name ==  "all")
    {
        for (unsigned int i = 0; i < _programList.size(); i++)
		{
			location = glGetUniformLocation(_programList[i]->handle(), varName);
            glUniformMatrix2fv(location, 1, 0, value);
        }
    }
	else
    {
		for (unsigned int i = 0; i < _programList.size(); i++)
		{
			if (_programList[i]->name() == name)
			{
				location = glGetUniformLocation(_programList[i]->handle(), varName);
				glUniformMatrix2fv(location, 1, 0, value);
				return;
			}
        }
    }
}
void MZShaderSystem::setUniform3d(GLfloat* value, char* varName, string name)
{
    GLuint location;
	if(name ==  "all")
    {
        for (unsigned int i = 0; i < _programList.size(); i++)
		{
			location = glGetUniformLocation(_programList[i]->handle(), varName);
            glUniform3fv(location, 1, value);
        }
    }
	else
    {
		for (unsigned int i = 0; i < _programList.size(); i++)
		{
			if (_programList[i]->name() == name)
			{
				location = glGetUniformLocation(_programList[i]->handle(), varName);
				glUniform3fv(location, 1, value);
				return;
			}
        }
    }
}
void MZShaderSystem::setUniform4m(GLfloat* value, char* varName, string name)
{
    GLuint location;
	if(name ==  "all")
    {
        for (unsigned int i = 0; i < _programList.size(); i++)
		{
			location = glGetUniformLocation(_programList[i]->handle(), varName);
            glUniformMatrix4fv(location, 1, 0, value);
        }
    }
	else
    {
		for (unsigned int i = 0; i < _programList.size(); i++)
		{
			if (_programList[i]->name() == name)
			{
				location = glGetUniformLocation(_programList[i]->handle(), varName);
				glUniformMatrix4fv(location, 1, 0, value);
				return;
			}
        }
    }
}
