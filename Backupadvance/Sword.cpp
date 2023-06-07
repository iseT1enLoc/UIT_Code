#include"Sword.h"
#include<iostream>
using namespace std;
Sword::Sword()
{
	blood = 100;
	damage = 68;
	armor = 10;
	type = 3;
}
void Sword::DrawSolider()
{
	cout << 'W';
}
void Sword::ShowStatistic()
{
	cout << "Sword solider.";
	cout << "\nBlood: " << blood;
	cout << "\nArmor: " << armor;
	cout << "\nDamage: " << damage;
}
void Sword::Ability()
{
	cout << "Stabbb";
}