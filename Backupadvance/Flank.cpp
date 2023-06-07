#include"Flank.h"
#include"Spear.h"
#include"Sword.h"
#include<iostream>
#include<algorithm>
using namespace std;

Flank::Flank()
{
	slot = 3;
	capacity = 60;
	isLeft = 1;
	curTotal = 0;
}

Flank::Flank(bool choose)
{
	isLeft = choose;
}
void Flank::EnterInitialStat()
{
	cout << "Enter number of Sword: ";
	cin >> FLnumSword;
	cout << "Enter number of Spear: ";
	cin >> FLnumSpear;
}
void Flank::arrange(vector<NonPowder*>& group)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			all[i][j] = nullptr;
		}
	}
	int full = 20;
	int cSlot = 0;
	//fill slot with sword
	for (int i = 0; i < group.size(); ++i)
	{
		if (full != 0)
		{
			if (cSlot == 3) return;
			if (dynamic_cast<Sword*>(group[i]) != nullptr)
			{
				all[20 - full][cSlot] = group[i];
				--full;
				++curTotal;
			}
		}
		else
		{
			++cSlot; full = 20;
			if (cSlot == 3) return;
			if (dynamic_cast<Sword*>(group[i]) != nullptr)
			{
				all[20 - full][cSlot] = group[i];
				--full;
				++curTotal;
			}
		}
	}


	++cSlot;
	full = 20;
	if (cSlot == 3) return;
	for (int i = 0; i < group.size(); ++i)
	{
		if (full != 0)
		{
			if (cSlot == 3) return;
			if (dynamic_cast<Spear*>(group[i]) != nullptr)
			{
				all[20 - full][cSlot] = group[i];
				--full;
				++curTotal;
			}
		}
		else
		{
			++cSlot; full = 20;
			if (cSlot == 3) return;
			if (dynamic_cast<Spear*>(group[i]) != nullptr)
			{
				all[20 - full][cSlot] = group[i];
				--full;
				++curTotal;
			}
		}
	}
	
	
	
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



