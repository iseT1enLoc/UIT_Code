#include"Powder.h"
#include<string>
#include<iostream>
using namespace std;


Powder::Powder()
{
	type = "Powder";
	damage = 500;
	blood = 100;
	armor = 15;
	munition = 10;
}
void Powder::Ability()
{
	cout << "Pang pang panggggg-> -> -> -> -> -> -> -> -> ->";
}
void Powder::ShowStatistic()
{
	cout << "This is the " << type;
	cout << "\nThe damage index is " << damage;
	cout << "\nThe blood of the " << type << " is " << blood;
	cout << "\nThe number of armor: " << armor;
	cout << "\nMunition: " << munition;
}
void Powder::DrawSolider()
{
	cout << "Powder";
}