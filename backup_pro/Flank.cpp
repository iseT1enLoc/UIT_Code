#include"Flank.h"
#include"Spear.h"
#include"Sword.h"
#include<iostream>
using namespace std;

Flank::Flank()
{
	slot = 3;
	capacity = 60;
	isLeft = 1;
	curTotal = 0;
}
void Flank::EnterInitialStat()
{
	cout << "Enter number of Sword: ";
	cin >> FLnumSword;
	cout << "Enter number of Spear: ";
	cin >> FLnumSpear;

	int tempW = FLnumSword;
	int tempP = FLnumSpear;

	int OK = 1;
	int ok = 0;
	
	int row = 0;
	int col = 0;

	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (ok)
			{
				if (tempP)
				{
					all[i][j] = new Spear;
					--tempP;
				}
				else
				{
					all[i][j] = NULL;
				}
			}
			if (OK)
			{
				if (tempW)
				{
					all[i][j] = new Sword;
					--tempW;
				}
				else
				{
					ok = 1;
					OK = 0;
					while (i < 20)
					{
						all[i++][j] = NULL;
					}
				}
			}
		}
	}
	
}
Flank::Flank(bool choose)
{
	this->isLeft = choose;
}
void Flank::Display()
{

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (all[i][j])
			{
				all[i][j]->DrawSolider();
				cout << '\t';
			}
		}
		cout << '\n';
	}
}
void Flank::AddSolidertoLine()
{
	int a;
	int b;
	cout << "The left blank potition is " << 60 - curTotal;
	cout << "\nEnter number of Sword you want to add: ";
	cin >> a;
	cout << "Enter number of Spear you want to add: ";
	cin >> b;
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (all[i][j] == NULL)
			{
				if (a)
				{
					all[i][j] = new Sword;
					--a; ++curTotal;
				}
				else if (b)
				{
					all[i][j] = new Spear;
					--b; ++curTotal;
				}
			}
		}
	}

}