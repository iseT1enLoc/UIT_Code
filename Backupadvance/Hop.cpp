#include"Hop.h"
#include<iostream>
using namespace std;
Hop::Hop()
{
	blood = 100;
	armor = 5;
	damage = 8;
	type = 2;
}
void Hop::DrawSolider()
{
	cout << 'H';
}
void Hop::ShowStatistic()
{
	cout << "Hop solider.";
	cout << "\nBlood: " << blood;
	cout << "\nArmor: " << armor;
	cout << "\nDamage: " << damage;
}
void Hop::Ability()
{
	cout << "Slahhhh";
}