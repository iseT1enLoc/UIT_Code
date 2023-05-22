#include"MONKIEMTRA.h"
#include<string>
#include<iostream>
using namespace std;

MONKIEMTRA::MONKIEMTRA()
{
	loai = 1;
}
MONKIEMTRA::MONKIEMTRA(string MaSo, string TenMonHoc,float HeSoMonHoc ,float HeSo1, float HeSo2, float HeSo3)
	:MONHOC(MaSo,TenMonHoc,HeSoMonHoc,HeSo1,HeSo2)
{
	this->HeSo3 =HeSo3;
}
MONKIEMTRA::~MONKIEMTRA()
{

}

void MONKIEMTRA::Nhap()
{
	cout << "Nhap he so mon kiem tra:  ";
	cin >> HeSoMonHoc;
	cin.ignore();
	cout << "Nhap ma so mon kiem tra: ";
	getline(cin, MaSo);
	cout << "Nhap ten mon kiem tra: ";
	getline(cin, TenMonHoc);
	cout << "Nhap diem he so 1: ";
	cin >> HeSo1;
	cout << "Nhap diem he so 2: ";
	cin >> HeSo2;
	cout << "Nhap diem he so 3: ";
	cin >> HeSo3;
}
void MONKIEMTRA::Xuat()
{
	cout << "Ma so mon kiem tra: " << MaSo;
	cout << "\nTen mon kiem tra: " << TenMonHoc;
	cout << "\nDiem he so 1: " << HeSo1;
	cout << "\nDiem he so 2: " << HeSo2;
	cout << "\nDiem he so 3: " << HeSo3;
	cout << "\nDiem tong ket: " << TinhDiemKetThucMonHoc();
}
float MONKIEMTRA::LayDiemKTHetMon()
{
	return HeSo3;
}

void MONKIEMTRA::CapNhatDiemKTHetMon(float HeSo3)
{
	this->HeSo3 = HeSo3;
}

float MONKIEMTRA::TinhDiemKetThucMonHoc()
{
	return (HeSo1 + HeSo2 * 2 + HeSo3 * 3) / 6;
}