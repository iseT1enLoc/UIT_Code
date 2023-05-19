#include"LongRange.h"
#include<iostream>
using namespace std;

LongRange::LongRange()
{
	slot = 8;
	capacity = 96;
	LnumPowder = total=0;
}
void LongRange::EnterStat()
{
	cout << "Enter number of Powder: ";
	cin >> LnumPowder;
	total = LnumPowder;

	Crows = 1.0 * total / 8;
	if ((int)Crows != Crows) ++Crows;

	int temp = total;
	for (int i = 0; i < Crows; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (temp)
			{
				all[i][j] = new Powder;
				--temp;
			}
		}
	}
}
void LongRange::Display()
{
	int temp = total;
	for (int i = 0; i < Crows; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (temp)
			{
				all[i][j]->DrawSolider();
				cout << '\t';
				--temp;
			}
		}
		cout << '\n';
	}
}