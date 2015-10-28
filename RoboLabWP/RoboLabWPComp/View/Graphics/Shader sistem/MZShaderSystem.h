#pragma once

#include "MZProgram.h"

#define SHADERSCOUNT 3

class MZShaderSystem
{
	static MZShaderSystem* instance;
	static int _refcount;
public:

	static MZShaderSystem* startSystem()
    {
		instance = new MZShaderSystem();
		_refcount = 0;
        return instance;
    }
	static MZShaderSystem* getInstance()
    {
		if(!instance)
		{
			startSystem();
		}
		_refcount++;
		return instance;
    }
	void FreeInst() { 
		_refcount--;
		if(!_refcount) {delete this; instance = NULL;}}

	
	GLuint getHandleByName(string name);
	void useProgramWithName(string name);

	void setAttribute(GLuint attribIndex, char* varName, string name);
	void setUniform1i(int value, char* varName, string name);
	void setUniform2m(GLfloat* value, char* varName, string name);
	void setUniform3d(GLfloat* value, char* varName, string name);
	void setUniform4m(GLfloat* value, char* varName, string name);

private:
	MZShaderSystem(void);
	virtual ~MZShaderSystem(void);
	MZShaderSystem(const MZShaderSystem& root);
	MZShaderSystem& operator=(const MZShaderSystem&);

	vector<MZProgram*> _programList;

};

