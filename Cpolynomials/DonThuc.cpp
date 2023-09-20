#include "DonThuc.h"
#include <iostream>
using namespace std;
DonThuc::DonThuc()
{

}
void DonThuc::Nhap()
{
	cout << "\nNhap he so: ";
	cin >> HeSo;
	cout << "\nNhap so mu: ";
	cin >> SoMu;
}
float DonThuc::LayHeSo()
{
	return HeSo;
}
int DonThuc::LaySoMu()
{
	return SoMu;
}
void DonThuc::GanSoMu(int SoMu)
{
	this->SoMu = SoMu;
}
void DonThuc::GanHeSo(float HeSo)
{
	this->HeSo = HeSo;
}
