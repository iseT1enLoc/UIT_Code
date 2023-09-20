#include"CBHopDong.h"
#include<iostream>
using namespace std;

void CBHopDong::Nhap()
{
	cout << "Nhap ma so can bo hop dong: ";
	getline(cin, MaSo);
	cout << "Nhap ho va ten can bo hop dong: ";
	getline(cin, HoTen);
	cout << "Nhap ngay sinh can bo hop dong: ";
	getline(cin, NgaySinh);
	cout << "Nhap tien cong: ";
	cin >> TienCong;
	cout << "Nhap so ngay cong: ";
	cin >> SoNgayCong;
	cout << "Nhap he so vuot gio: ";
	cin >> HeSoVuotGio;
}
float CBHopDong::TinhLuong()
{
	return TienCong * SoNgayCong * HeSoVuotGio;
}
void CBHopDong::Xuat()
{
	cout << "Can bo " << Loai << '.';
	cout << "\nMa so: " << MaSo;
	cout << "\nHo va ten can bo: " << HoTen;
	cout << "\nLuong: " << TinhLuong();
	cout << "\nTien cong: " << TienCong;
	cout << "\nSo ngay cong: " << SoNgayCong;
	cout << "\nHe so vuot gio: " << HeSoVuotGio;
}