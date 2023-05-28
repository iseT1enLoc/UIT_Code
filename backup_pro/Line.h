#pragma once
class Line
{
protected:
	int slot;
	int capacity;
	int curTotal;
public:
	Line();
	virtual void EnterInitialStat()=0;
	virtual void Display()=0;
	virtual void AddSolidertoLine()=0;
};