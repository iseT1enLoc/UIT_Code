#include"Sword.h"
#include<iostream>
using namespace std;

Sword::Sword()
{
	type = "Sword";
	damage = 60;
	blood = 75;
	armor = 5;
}
void Sword::Ability()
{
	cout << "Stabbbbbbbbbbbb";
}
void Sword::DrawSolider()
{
	cout << "Sword";
}