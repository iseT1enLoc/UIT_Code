#include"Spear.h"
#include<iostream>
using namespace std;

Spear::Spear()
{
	blood = 100;
	damage = 90;
	armor = 8;
}
void Spear::DrawSolider()
{
	cout << "P";
}
void Spear::ShowStatistic()
{
	cout << "Spear solider.";
	cout << "\nBlood: " << blood;
	cout << "\nArmor: " << armor;
	cout << "\nDamage: " << damage;
}
void Spear::Ability()
{
	cout << "Throwinggg";
}