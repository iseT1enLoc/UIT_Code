#include"GiangVien.h"
#include<iostream>
using namespace std;
void GiangVien::Nhap()
{
	cout << "Nhap ma so giang vien: ";
	getline(cin, MaSo);
	cout << "Nhap ho va ten giang vien: ";
	getline(cin, HoTen);
	cout << "Nhap ngay thang nam sinh giang vien: ";
	getline(cin, NgaySinh);
	cout << "Nhap so tiet giang day trong nam: ";
	cin >> SoTiet;
	cout << "Nhap so de tai khoa luan ma giang vien huong dan: ";
	cin >> SoDeTaiKL;
}
void GiangVien::Xuat()
{
	cout << "Ma so giang vien: " << MaSo;
	cout << "\nHo va ten giang vien: " << HoTen;
	cout << "\nNgay thang nam sinh: " << NgaySinh;
	cout << "\nSo tiet giang day trong nam: " << SoTiet;
	cout << "\nSo de tai khoa luan ma giang vien huong dan: " << SoDeTaiKL;
}
bool GiangVien::DuTieuChuan()
{
	return SoTiet >= 300 && SoDeTaiKL >= 5;
}
