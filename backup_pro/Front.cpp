#include<iostream>
#include"Sword.h"
#include"Spear.h"
#include"Hop.h"
#include"Front.h"

Front::Front()
{
	slot = 8;
	capacity = 240;
	curTotal = 0;
}
void Front::EnterInitialStat()
{
	cout << "Enter the number of Sword: ";
	cin >> nSword;
	cout << "Enter the number of Spear: ";
	cin >> nSpear;
	cout << "Enter the number of Hop: ";
	cin >> nHop;
	

	int a = nSword;
	int b = nSpear;
	int c = nHop;

	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j <8; ++j)
		{
			if (a)
			{
				all[i][j] = new Sword;
				--a;
				++curTotal;
			}
			else if (b)
			{
				all[i][j] = new Spear;
				--b;
				++curTotal;
			}
			else if (c)
			{
				all[i][j] = new Hop;
				--c;
				++curTotal;
			}
			else all[i][j] = NULL;
		}
	}

}
void Front::Display()
{
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (all[i][j]!=NULL)
			{
				all[i][j]->DrawSolider();
			}
			cout << ' ';
		}
		cout << '\n';
	}
}
void Front::AddSolidertoLine()
{
	int nW;
	int nH;
	int nP;
	cout << "The left blank potition is " << 96 - curTotal;
	cout << "\nHow many Swords do you want to add: ";
	cin >> nW;
	cout << "How many Spears do you want to add: ";
	cin >> nP;
	cout << "How many Hops do you want to add: ";
	cin >> nH;
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (all[i][j] == NULL)
			{
				if (nW)
				{
					all[i][j] = new Sword;
					--nW;
					++curTotal;
				}
				else if (nP)
				{
					all[i][j] = new Spear;
					--nP;
					++curTotal;
				}
				else if(nH)
				{
					all[i][j] = new Hop;
					--nH;
					++curTotal;
				}
			}
		}
	}
}