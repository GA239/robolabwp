#pragma once

//
//  MZVisitsMatrix.h
//
//  �����, ���������� �������������� ���������� ������� �������� ������� ���������� ��������� ������ ��������� ������. ��� ���������� ���������� ��, ��� ������ ���� ����� � ������ �������� � ���������.


#include "Model\Basic Types\MZPosition.h";
#include "Model\Basic Types\MZMacro.h"
#include <vector>;

using namespace std;

class MZVisitsMatrix
{
public:
	MZVisitsMatrix(int width, int height);
	virtual ~MZVisitsMatrix(void);

	int lastVisitAtPosition(MZPosition* position);
	double visibilityAtXY(int x, int y);
	void setLastVisitAtStepAtPosition(int step, MZPosition *position);

private:
	vector<vector<int>> _visits;
    int _width, _height;


};

