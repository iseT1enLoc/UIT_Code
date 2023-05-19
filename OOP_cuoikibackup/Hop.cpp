#include"Hop.h"
#include<iostream>
using namespace std;


Hop::Hop()
{
	type = "Hop";
	damage = 100;
	blood = 100;
	armor = 5;
}
void Hop::Ability()
{
	cout << "Slashhhhhh";
}
void Hop::DrawSolider()
{
	cout << "Hop";
}