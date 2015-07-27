#pragma once

//
//  MZCellMatrix.h
//  Maze
//
//  Created by Admin on 03.02.15.
//  Copyright (c) 2015 KirillStalnov. All rights reserved.
//
//   ласс, €вл€ющийс€ представлением двумерного массива объектов класса MZCell.


#include "Model\Basic Types\MZPosition.h";
#include "Model\Game\MZCell.h";
#include <vector>;

using namespace std;

class MZCellMatrix
{
public:
	MZCellMatrix(int width, int height);
	virtual ~MZCellMatrix(void);

	MZCell* cellAtPosition(MZPosition * position);

private:
	vector<vector<MZCell*>> _cells;

};

