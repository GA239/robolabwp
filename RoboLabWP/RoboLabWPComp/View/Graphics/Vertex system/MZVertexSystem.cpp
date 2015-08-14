#include "pch.h"
#include "MZVertexSystem.h"
#include "MZVertexArrayObject.h"
#include  "View\Graphics\Shader sistem\MZShaderSystem.h"

MZVertexSystem* MZVertexSystem::instance;
int MZVertexSystem::_refcount;

static float vertexTextureCoordsData[] =
{
    0.0, 0.0,
    0.0, 1.0,
    1.0, 1.0,
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0
};

static float vertexPositionCoordsData[] =
{
    0.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    0.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 1.0, 0.0
};

MZVertexSystem::MZVertexSystem(void)
{
	_vertexTextureCoordsData = vertexTextureCoordsData;
    _vertexPositionCoordsData = vertexPositionCoordsData;

	MZVertexBuffer *positionCoordBuffer = new MZVertexBuffer(POSITION_COORDS_BUFFER, _vertexPositionCoordsData, sizeof(float) * 18, "positionCoords");
    MZVertexBuffer *textureCoordBuffer = new MZVertexBuffer(TEXTURE_COORDS_BUFFER, _vertexTextureCoordsData, sizeof(float) * 12, "textureCoords");
    _particlePropertiesBuffer = NULL;
    _particlePositionBuffer = NULL;
    
    _vertexArrayObject = new MZVertexArrayObject();
	_vertexArrayObject->addVertexBuffer(positionCoordBuffer);
    _vertexArrayObject->addVertexBuffer(textureCoordBuffer);
    
    //_geometryList = [[NSMutableDictionary alloc] init];
    
    MZGeometry *squareGeometry = new MZGeometry();
    
    squareGeometry->addVertexBuffer(positionCoordBuffer);
    squareGeometry->addVertexBuffer(textureCoordBuffer);
    
    squareGeometry->bindInProgram("texture");
    squareGeometry->bindInProgram("color");
    squareGeometry->prepare();
	squareGeometry->setName("square");
    
	_geometryList.push_back(squareGeometry);
}


MZVertexSystem::~MZVertexSystem(void)
{
	delete(_vertexArrayObject);
	for (unsigned int i = 0; i < _geometryList.size(); i++)
	{
		if (_geometryList[i] != NULL)
		{
			delete(_geometryList[i]);
		}
	}
}

void MZVertexSystem::useGeometryWithName(string name)
{
    //[[_geometryList objectForKey:name] prepare];
	for (unsigned int i = 0; i < _geometryList.size(); i++)
	{
		if(_geometryList[i]->name() == name)
		{
			_geometryList[i]->prepare();
		}
	}
}
MZGeometry* MZVertexSystem::getGeometryWithName(string name)
{
	//return [_geometryList objectForKey:name];
	for (unsigned int i = 0; i < _geometryList.size(); i++)
	{
		if(_geometryList[i]->name() == name)
		{
			return _geometryList[i];
		}
	}
	return NULL;
}
void MZVertexSystem::setGeometry(MZGeometry * geometry, string name)
{
    //[_geometryList setObject:geometry forKey:name];
	geometry->setName(name);
	_geometryList.push_back(geometry);

    //for (MZVertexBuffer * buffer in [geometry bufferList])
	for (unsigned int i = 0; i < geometry->bufferList().size(); i++)
    {
		//[_vertexArrayObject addVertexBuffer:buffer];
        _vertexArrayObject->addVertexBuffer(geometry->bufferList()[i]);
    }
}