#pragma once
#include"Line.h"
#include"NonPowder.h"
class Flank :public Line
{
public:
	NonPowder* all[20][3];
protected:
	bool isLeft;
	int FLnumSword;
	int FLnumSpear;
public:
	Flank();
	Flank(bool);
	void EnterInitialStat();
	void Display();
	void AddSolidertoLine();
};