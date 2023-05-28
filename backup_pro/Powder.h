#pragma once
#include"Solider.h"
class Powder:public Solider
{
protected:
	int munition;
public:
	Powder();
	void DrawSolider();
	void ShowStatistic();
	void Ability();
};