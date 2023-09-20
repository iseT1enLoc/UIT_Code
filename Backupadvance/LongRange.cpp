#include"LongRange.h"
#include<iostream>
using namespace std;

LongRange::LongRange()
{
	slot = 8;
	capacity = 96;
	curTotal = 0;
}
void LongRange::EnterInitialStat()
{
	cout << "Enter number of Powders: ";
	cin >> nPowder;
	int a = nPowder;
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (a)
			{
				all[i][j] = new Powder;
				--a;
				++curTotal;
			}
			else all[i][j] = NULL;
		}
	}
}
void LongRange::Display()
{
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (all[i][j] != NULL)
			{
				all[i][j]->DrawSolider();
				cout << " ";
			}
		}
		cout << "\n";
	}
}
void LongRange::AddSolidertoLine()
{
	int a;
	if (curTotal == 96)
	{
		cout << "\nLine is full.";
		return;
	}
	cout << "The left blank potition of LongRange is " << 96 - curTotal;
	cout << "\nEnter the number of Powder you want to add: ";
	cin >> a;
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (all[i][j] == NULL)
			{
				if (a)
				{
					all[i][j] = new Powder;
					--a;
					++curTotal;
				}
			}
		}
	}
}