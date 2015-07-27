#pragma once

#include "Model\Basic Types\MZPosition.h";
#include "MZTarget.h"

class MZButton
{
public:
	MZButton(MZPosition * position, MZDirection direction, MZTarget* target);
	virtual ~MZButton(void);

	MZPosition * position();
	MZDirection direction();
	bool isActivated();
	void activate();

private:
	MZPosition * _position;
    MZDirection _direction;
    MZTarget* _target;
    bool _isActivated;
};

