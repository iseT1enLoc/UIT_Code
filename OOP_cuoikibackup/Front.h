#pragma once
#include"Line.h"
#include"NonPowder.h"
class Front:public Line
{
protected:
	NonPowder* all[30][8];
	int FnumHop;
	int FnumSpear;
	int FnumSword;
public:
	Front();
	void Display();
	void EnterStat();
};
