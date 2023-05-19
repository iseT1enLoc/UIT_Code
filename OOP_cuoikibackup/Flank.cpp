#include"Flank.h"
#include"Sword.h"
#include"Spear.h"
#include<iostream>
using namespace std;

Flank::Flank()
{
	slot = 3;
	capacity = 60;
	isLeft = 1;
	FLnumSpear = FLnumSword = total=0;
}
int Flank::isleft(int x)
{
	isLeft = x;
	return isLeft;
}
void Flank::EnterStat()
{
	cout << "Enter number of Sword: ";
	cin >> FLnumSword;
	cout << "\nEnter number of Spear: ";
	cin >> FLnumSpear;
	total = FLnumSword + FLnumSpear;

	Ccols = 1.0*total / 20;//1.0 mean type conversion

	int tempW = FLnumSword;
	int tempP = FLnumSpear;
	if (Ccols != (int)Ccols) ++Ccols;

	for (int j = 0; j < Ccols; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (tempW)
			{
				all[i][j] = new Sword;
				--tempW;
			}
			else if (tempP)
			{
				all[i][j] = new Spear;
				--tempP;
			}
		}
	}
}
void Flank::Display()
{
	int temp = total;
	for (int j = 0; j < Ccols; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (total)
			{
				all[i][j]->DrawSolider();
				cout << '\n';
				--total;
			}
		}
		cout << '\t';
	}
}