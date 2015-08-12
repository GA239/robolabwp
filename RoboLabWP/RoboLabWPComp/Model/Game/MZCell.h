#pragma once
//
//  MZCell.h
//
//  Класс, объект которого хранит данные о клетке лабиринта. Не изменяется после построения лабиринта.

#include "Model\Basic Types\MZByte.h"
#include "Model\Basic Types\MZDirection.h"

class MZCell
{
public:
	MZCell(void);
	MZCell(MZByte walls);
	virtual ~MZCell(void);

	void setWallsValue(MZByte walls);
	MZByte wallsValue(void);
	bool hasWallAtDirection(MZDirection direction);

	bool isEmpty;

private:
	 MZByte _walls;
};

