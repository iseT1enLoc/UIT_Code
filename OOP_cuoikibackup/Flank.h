#pragma once
#include"Line.h"
#include"NonPowder.h"
class Flank :public Line
{
protected:
	bool isLeft;
	NonPowder* all[20][3];
	int FLnumSword;
	int FLnumSpear;
	float Ccols;
public:
	Flank();
	int isleft(int);
	void EnterStat();
	void Display();
};