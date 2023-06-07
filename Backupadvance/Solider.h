#pragma once
class Solider
{
protected:
	int blood;
	int armor;
	int damage;
	int type;//1-powder,2-hop,3-sword,4-spear;
public:
	Solider();
	virtual void ShowStatistic() = 0;
	virtual void DrawSolider() = 0;//'P' powder,'W'sword,'P'spear,'H' hop
	virtual void Ability() = 0;
	int GetType();
};
