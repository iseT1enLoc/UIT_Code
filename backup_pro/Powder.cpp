#include"Powder.h"
#include<iostream>
using namespace std;
Powder::Powder()
{
	blood=200;
    armor=5;
	damage=100;
	type=1;
}
void Powder::DrawSolider()
{
	cout << '*';
}
void Powder::ShowStatistic()
{
	cout << "Powder";
	cout << "\nBlood: " << blood;
	cout << "\nArmor: " << armor;
	cout << "\nDamage: " << armor;
	cout << "\nMunition: " << munition;
}
void Powder::Ability()
{
	cout << "-	-	-	-	-	>>>>";
}