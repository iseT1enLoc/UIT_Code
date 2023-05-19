#include"NonPowder.h"
#include<iostream>

NonPowder::NonPowder()
{
	type = "N/D";
	damage = 0;
	blood = 0;
	armor = 0;
}
void NonPowder::DrawSolider()
{
	cout << "---";
}
void NonPowder::ShowStatistic()
{
	cout << "This is the " << type;
	cout << "\nThe damage index is " << damage;
	cout << "\nThe blood of the " << type << " is " << blood;
	cout << "\nThe number of armor: " << armor;
}