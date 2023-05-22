#include<iostream>
#include"MONHOC.h"
using namespace std;

MONHOC::MONHOC()
{

}
MONHOC::MONHOC(string MaSo, string TenMonHoc,float HeSoMonHoc ,float HeSo1,float HeSo2)
{
	this->HeSoMonHoc = HeSoMonHoc;
	this->MaSo = MaSo;
	this->TenMonHoc = TenMonHoc;
	this->HeSo1 = HeSo1;
	this->HeSo2 = HeSo2;
}

int MONHOC::LayLoai()
{
	return loai;
}
string MONHOC::LayMaSo()
{
	return MaSo;
}
void MONHOC::CapNhatMaSo(string MaSo)
{
	this->MaSo = MaSo;
}

string MONHOC::LayTenMonHoc()
{
	return TenMonHoc;
}
void MONHOC::CapNhatTenMonHoc(string TenMonHoc)
{
	this->TenMonHoc = TenMonHoc;
}

float MONHOC::LayHeSo1() {
	return HeSo1;
}
void MONHOC::CapNhatHeSo1(float HeSo1)
{
	this->HeSo1 = HeSo1;
}

float MONHOC::LayHeSo2()
{
	return HeSo2;
}
void MONHOC::CapNhatHeSo2(float HeSo2)
{
	this->HeSo2 = HeSo2;
}
float MONHOC::LayHeSoMonHoc()
{
	return HeSoMonHoc;
}
