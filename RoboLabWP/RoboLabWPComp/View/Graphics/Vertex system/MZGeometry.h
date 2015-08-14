#pragma once

#include "MZVertexBuffer.h"
#include <string>
#include <vector>

using namespace std;

class MZGeometry
{
public:
	MZGeometry(void);
	virtual ~MZGeometry(void);

	void addVertexBuffer(MZVertexBuffer* vertexBuffer);
	vector<MZVertexBuffer*> bufferList();
	void bindInProgram( string  programName);
	void prepare();

	void setName(string name);

	string name();

private:

	string _name;

	vector<MZVertexBuffer*> _bufferList;
	vector<string> _programList;
};

