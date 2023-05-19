#include"Spear.h"
#include<iostream>
using namespace std;

Spear::Spear()
{
	type = "Spear";
	damage = 150;
	blood = 79;
	armor = 5;
}
void Spear::Ability()
{
	cout << "Throwingggg";
}
void Spear::DrawSolider()
{
	cout << "Spear";
}