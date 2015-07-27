#pragma once

//
//  MZRotatingCell.h
//  Robo Lab
//
#include "Model\Basic Types\MZPosition.h";
#include "Model\Basic Types\MZDirection.h";
#include "Model\Basic Types\MZByte.h";
#include "Model\Basic Types\MZRotationDirection.h";
#include "Model\Game\MZCell.h";
#include "Model\Game\Game Objects\MZTarget.h";

class MZRotatingCell :
	public MZTarget
{
public:
	MZRotatingCell(MZPosition* position, MZCell* cell, MZRotationDirection rotationDirection);
	virtual ~MZRotatingCell(void);

	MZPosition* position();
	bool hasWallAtDirection(MZDirection direction);
	MZRotationDirection rotationDirection();
	void toggle();

private:
	MZPosition * _position;
    MZCell *_cell;
    MZRotationDirection _rotationDirection;
};

