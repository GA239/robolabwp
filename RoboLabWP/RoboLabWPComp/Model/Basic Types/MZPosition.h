#pragma once

#include "MZDirection.h"

class MZPosition
{
public:
	MZPosition(int x, int y);
	MZPosition(MZPosition &obj);
    
	~MZPosition(void);

	int x(void);
	int y(void);
	void move(MZDirection direction);
	MZPosition* copy(void);
	bool equals(MZPosition *otherPosition);

private:
	int _x;
    int _y;
};

