#include"Bo.h"
#include<iostream>
using namespace std;
void Bo::TiengKeu()
{
	cout << "ummmm boooooo";
}
int Bo::ChoSua()
{
	return rand()%20;
}
int Bo::SinhCon()
{
	return 1+rand()%5;
}
string Bo::ten()
{
	return Ten;
}