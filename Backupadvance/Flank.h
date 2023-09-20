#pragma once
#include"Line.h"
#include"NonPowder.h"
#include<vector>
using namespace std;
class Flank :public Line
{
public:
	NonPowder* all[20][3];
protected:
	bool isLeft;
public:
	int FLnumSword;
	int FLnumSpear;
public:
	Flank();
	Flank(bool);
	void arrange(vector<NonPowder*>&group); //chua lam duoc
	void EnterInitialStat();
	void Display();
	void AddSolidertoLine();
};