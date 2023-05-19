#pragma once
#include<string>
using namespace std;

class Solider
{
protected:
	string type;
	int damage;
	int blood;
	int armor;
public:
	Solider();
	virtual void Ability();
	virtual void ShowStatistic();
	virtual void DrawSolider();
};