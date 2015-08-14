#pragma once

#include "MZVertexBufferType.h"
#include "GLES2/gl2.h"

class MZVertexBuffer
{
public:
	MZVertexBuffer(MZVertexBufferType type, float* data, int count, char* name);
	~MZVertexBuffer(void);

	GLuint handle();
	int valuesPerVertice();
	void freeBuffer();
	char* name();

	MZVertexBufferType _type;
	//char * name;

private:
	GLuint _handle;
    int _valuesPerVertice;
    int _count;
    char* _name;
};

