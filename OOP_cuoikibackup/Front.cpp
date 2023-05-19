#include"Front.h"
#include"Spear.h"
#include"Sword.h"
#include"Hop.h"
#include<iostream>
using namespace std;
Front::Front()
{
	slot = 8;
	capacity = 240;
	FnumHop = FnumSpear = FnumSword = total=0;
}
void Front::EnterStat()
{
	cout << "Enter number of Spear: ";
	cin >> FnumSpear;
	cout << "Enter number of Sword: ";
	cin >> FnumSword;
	cout << "Enter number of Hop: ";
	cin >> FnumHop;

	total = FnumSpear + FnumSword + FnumHop;
	Crows = 1.0*total / 8;
	if ((int)Crows !=Crows) ++Crows;
	//neu so nguyen la chia het còn khong nguyen thì them mot hang nua

	if (FnumSpear)
	{
		for (int i = 0; i < Crows; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (FnumSpear)
				{
					all[i][j] = new Spear;
					--FnumSpear;
				}
				else if (FnumSword)
				{
					all[i][j] = new Sword;
					--FnumSword;
				}
				else if (FnumHop)
				{
					all[i][j] = new Hop;
					--FnumHop;
				}
			}
		}
	}
}
void Front::Display()
{
	for (int i = 0; i < Crows; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (total)
			{
				all[i][j]->DrawSolider();
				cout << '\t';
				--total;
			}
		}
		cout << '\n';
	}
	
}