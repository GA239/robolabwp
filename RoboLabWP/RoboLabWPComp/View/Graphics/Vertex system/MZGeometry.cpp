#include "pch.h"
#include "MZGeometry.h"
#include  "View\Graphics\Shader sistem\MZShaderSystem.h"


MZGeometry::MZGeometry(void)
{
}

void MZGeometry::setName(string name)
{
	_name = name;
}
string MZGeometry::name()
{
	return _name;
}
MZGeometry::~MZGeometry(void)
{
	for (unsigned int i = 0; i < _bufferList.size(); i++)
	{
		if (_bufferList[i] != NULL)
		{
			delete(_bufferList[i]);
			_bufferList[i] = NULL;
		}
	}
}

void MZGeometry::addVertexBuffer(MZVertexBuffer* vertexBuffer)
{
	_bufferList.push_back(vertexBuffer);
}
vector<MZVertexBuffer*> MZGeometry::bufferList()
{
    return _bufferList;
}
void MZGeometry::bindInProgram( string  programName)
{
	_programList.push_back(programName);
}
void MZGeometry::prepare()
{
	// по ходу эта функция не нужна !!!!!!
	//так же по ходу не нужна ShaderSystem->setAttribute !!!!!

	MZShaderSystem* ShaderSystem = MZShaderSystem::getInstance();
	for (unsigned int programName = 0; programName < _programList.size(); programName++)
    {
		for (unsigned int buffer = 0; buffer < _bufferList.size(); buffer++)
        {
			ShaderSystem->setAttribute(_bufferList[buffer]->_type,_bufferList[buffer]->name(),_programList[programName]);
            //[[MZShaderSystem getInstance] setAttributeIndex:[buffer type] forVariable:[buffer name] inProgram:programName];
        }
        //[[MZShaderSystem getInstance] linkProgramWithName:programName];
    }
	ShaderSystem->FreeInst();
}
