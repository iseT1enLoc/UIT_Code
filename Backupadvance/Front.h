#pragma once
#include"Line.h"
#include"NonPowder.h"
#include<iostream>
using namespace std;

class Front :public Line
{

public:
	NonPowder* all[30][8];
protected:
	int nHop;
	int nSpear;
	int nSword;
public:
	Front();
	void EnterInitialStat();
	void Display();
	void AddSolidertoLine();
};

