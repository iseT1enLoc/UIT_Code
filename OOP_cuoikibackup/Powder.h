#pragma once
#include"Solider.h"

class Powder:public Solider
{
protected:
	int munition;
public:
	Powder();
	void Ability();
	void ShowStatistic();
	void DrawSolider();
};