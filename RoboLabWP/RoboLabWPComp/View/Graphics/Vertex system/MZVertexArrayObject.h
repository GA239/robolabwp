#pragma once
//
//  MZVertexArrayObject.h
//  Robo Lab
//

#include "MZVertexBuffer.h"

class MZVertexArrayObject
{
public:
	MZVertexArrayObject(void);
	virtual ~MZVertexArrayObject(void);

	GLuint handle();
	void addVertexBuffer(MZVertexBuffer * vertexBuffer);
	void bind();

private:
	GLuint _handle;
	int _verticesCount;

};

