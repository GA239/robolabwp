#pragma once

#include "MZVertexArrayObject.h"
#include "MZGeometry.h"

class MZVertexSystem
{

	static MZVertexSystem* instance;
	static int _refcount;

public:

	static MZVertexSystem* startSystem()
    {
		instance = new MZVertexSystem();
		_refcount = 0;
        return instance;
    }
	static MZVertexSystem* getInstance()
    {
		if(!instance)
		{
			startSystem();
		}
		_refcount++;
		return instance;
    }
	void FreeInst() { _refcount--; if(!_refcount) {delete this; instance = NULL;}}

	void useGeometryWithName(string name);
	MZGeometry * getGeometryWithName(string name);
	void setGeometry(MZGeometry * geometry, string name);

private:
	MZVertexSystem(void);
	virtual ~MZVertexSystem(void);
	MZVertexSystem(const MZVertexSystem& root);
	MZVertexSystem& operator=(const MZVertexSystem&);

	//NSMutableDictionary *_geometryList;
	vector<MZGeometry*> _geometryList;
    MZVertexArrayObject *_vertexArrayObject;
    
    float *_vertexTextureCoordsData;
    float *_vertexPositionCoordsData;
    float *_particlePropertiesBuffer;
    float *_particlePositionBuffer;

};

