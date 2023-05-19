#pragma once

class Line
{
protected:
	int total;//to store the total Solider
	float Crows;//to save the current rows
	int slot;
	int capacity;
public:
	Line();
	virtual void Display();
	virtual void EnterStat();
};