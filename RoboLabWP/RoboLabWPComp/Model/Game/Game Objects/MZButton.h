#pragma once
#include "MZGameObject.h";

#include "Model\Basic Types\MZPosition.h";
#include "MZTarget.h"

class MZButton :
	public MZGameObject
{
public:
	MZButton(MZPosition * position, MZDirection direction, MZTarget* target);
	virtual ~MZButton(void);

	void init() {}

	MZPosition * position();
	MZDirection direction();
	bool isActivated();
	void activate();
	MZGameObjectName info() {return BUTTON;}

private:
	MZPosition * _position;
    MZDirection _direction;
    MZTarget* _target;
    bool _isActivated;
};

