#pragma once
#include"Line.h"
#include"Powder.h"
class LongRange:public Line
{
protected:
	Powder* all[12][8];
	int LnumPowder;
public:
	LongRange();
	void EnterStat();
	void Display();
};