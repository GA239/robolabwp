#include "pch.h"
#include "MZVertexBuffer.h"


MZVertexBuffer::MZVertexBuffer(MZVertexBufferType type, float* data, int count, char* name)
{
	glGenBuffers(1, &_handle);

    _type = type;
    _count = count;
    _name = name;
    
    glBindBuffer(GL_ARRAY_BUFFER, _handle);
    glBufferData(GL_ARRAY_BUFFER, _count, data, GL_STATIC_DRAW);

	switch(type)
    {
        case POSITION_COORDS_BUFFER:
            _valuesPerVertice = 3;
            break;
        case TEXTURE_COORDS_BUFFER:
            _valuesPerVertice = 2;
            break;
        case PARTICLE_STARTING_POSITION_BUFFER:
            _valuesPerVertice = 3;
            break;
        case PARTICLE_PROPERTIES_BUFFER:
            _valuesPerVertice = 4;
            break;
    }
}


MZVertexBuffer::~MZVertexBuffer(void)
{
}


GLuint MZVertexBuffer::handle()
{
    return _handle;
}
int MZVertexBuffer::valuesPerVertice()
{
    return _valuesPerVertice;
}
void MZVertexBuffer::freeBuffer()
{
    glDeleteBuffers(1, &_handle);
}

char* MZVertexBuffer::name()
{
	return _name;
}