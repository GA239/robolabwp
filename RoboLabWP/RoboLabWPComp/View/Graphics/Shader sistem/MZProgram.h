#pragma once

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"

#include <string>
#include <vector>

using namespace std;

class MZProgram
{
public:
	MZProgram(string name);
	virtual ~MZProgram(void);

	void use();
	GLuint handle();
	void initWithName();
	string name();

private:
	GLuint _handle;
	string _name;
};

