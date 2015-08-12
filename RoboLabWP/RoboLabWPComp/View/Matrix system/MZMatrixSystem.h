#pragma once

//
//  MZMatrixSystem.h
//  Robo Lab
//
#include "Model\Basic Types\MZMacro.h"
//#include "MZShaderSystem.h"
#include <vector>
#include "glm\glm.hpp"

using namespace glm;
using namespace std;


class MZMatrixSystem
{
	static MZMatrixSystem* instance;
	static int _refcount;

public:

	static MZMatrixSystem* startSystem()
    {
		instance = new MZMatrixSystem();
		_refcount = 0;
        return instance;
    }
	static MZMatrixSystem* getInstance()
    {
		if(!instance)
		{
			startSystem();
		}
		_refcount++;
		return instance;
    }
	void FreeInst() { _refcount--; if(!_refcount) {delete this; instance = NULL;}}


	void translateWithVector3(vec3 vector);
	void translate(double x, double y, double z);
	void scale(double x,  double y, double z);
	void pop();
	void prepare();
	void setProjectionWithZoom(double zoom);

private:
	MZMatrixSystem(void);
	virtual ~MZMatrixSystem(void);
	MZMatrixSystem(const MZMatrixSystem& root);
	MZMatrixSystem& operator=(const MZMatrixSystem&);
	
	mat4  _viewMatrix;
    mat4 _modelMatrix;
    mat4 _projectionMatrix;
    //GLKMatrixStackRef _matrixStackReference;
	vector<mat4> _matrixStackReference;
};

