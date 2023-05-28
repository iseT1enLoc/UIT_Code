#pragma once
#include"Powder.h"
#include"Line.h"
class LongRange:public Line
{
public:
	Powder* all[12][8];
protected:
	int nPowder;
public:
	LongRange();
	void EnterInitialStat();
	void Display();
	void AddSolidertoLine();
};