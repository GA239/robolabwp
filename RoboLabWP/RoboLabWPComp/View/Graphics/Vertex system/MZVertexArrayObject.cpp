#include "pch.h"
#include "MZVertexArrayObject.h"

MZVertexArrayObject::MZVertexArrayObject(void)
{
	//glGenVertexArraysOES(1, &_handle);
    //glBindVertexArrayOES(_handle);
}

MZVertexArrayObject::~MZVertexArrayObject(void)
{
}

GLuint MZVertexArrayObject::handle()
{
    return _handle;
}
void MZVertexArrayObject::addVertexBuffer(MZVertexBuffer * vertexBuffer)
{
	//glBindVertexArrayOES(_handle);
    
	glEnableVertexAttribArray(vertexBuffer->_type);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->handle());
	glVertexAttribPointer(vertexBuffer->_type, vertexBuffer->valuesPerVertice(), GL_FLOAT, GL_FALSE, 0 , 0);
}
void MZVertexArrayObject::bind()
{
    //glBindVertexArrayOES(_handle);
}
