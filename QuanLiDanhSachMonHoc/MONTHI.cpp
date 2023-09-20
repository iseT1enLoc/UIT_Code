#include"MONTHI.h"
#include<iostream>
using namespace std;

MONTHI::MONTHI()
{
	loai = 2;
}
string MaSo;
string TenMonHoc;
float HeSo1;
float HeSo2;
MONTHI::MONTHI(string MaSo, string TenMonHoc,float HeSoMonHoc ,float HeSo1, float HeSo2, float DiemThiHetMon)
	:MONHOC(MaSo,TenMonHoc,HeSoMonHoc,HeSo1,HeSo2)
{
	this->DiemThiHetMon = DiemThiHetMon;
}
MONTHI::~MONTHI()
{

}

void MONTHI::Nhap()
{
	cout << "Nhap he so mon thi: ";
	cin >> HeSoMonHoc;
	cin.ignore();
	cout << "Nhap ma so mon thi: ";
	getline(cin, MaSo);
	cout << "Nhap ten mon thi: ";
	getline(cin, TenMonHoc);
	cout << "Nhap diem he so 1: ";
	cin >> HeSo1;
	cout << "Nhap diem he so 2: ";
	cin >> HeSo2;
	cout << "Nhap diem thi het mon hoc: ";
	cin >> DiemThiHetMon;
}

void MONTHI::Xuat()
{
	cout << "Ma so mon thi: " << MaSo;
	cout << "\nTen mon thi: " << TenMonHoc;
	cout << "\nDiem he so 1: " << HeSo1;
	cout << "\nDiem he so 2: " << HeSo2;
	cout << "\nDiem thi ket thuc mon hoc: " << DiemThiHetMon;
	cout << "\nDiem tong ket: " << TinhDiemKetThucMonHoc();
}

float MONTHI::LayDiemThiHetMon()
{
	return DiemThiHetMon;
}
void MONTHI::CapNhatDiemThiHetMon(float DiemThiHetMon)
{
	this->DiemThiHetMon = DiemThiHetMon;
}

float MONTHI::DiemTrungBinhKiemTra()
{
	return (HeSo1 + HeSo2 * 2) / 3;
}
float MONTHI::TinhDiemKetThucMonHoc()
{
	return (DiemTrungBinhKiemTra() + DiemThiHetMon) / 2;
}