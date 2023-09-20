#include"CBBienChe.h"
#include<iostream>
using namespace std;

void CBBienChe::Nhap()
{
	cout << "Nhap ma so can bo bien che: ";
	getline(cin, MaSo);
	cout << "Nhap ho va ten can bo bien che: ";
	getline(cin, HoTen);
	cout << "Nhap ngay sinh can bo bien che: ";
	getline(cin, NgaySinh);
	cout << "Nhap vao luong co ban cua can bo bien che: ";
	cin >> LuongCoBan;
	cout << "Nhap vao he so luong cua can bo bien che: ";
	cin >> HeSoLuong;
	cout << "Nhap vao he so phu cap cua can bo bien che: ";
	cin >> HeSoPhuCap;
}
float CBBienChe::TinhLuong()
{
	return LuongCoBan * HeSoLuong * HeSoPhuCap;
}
void CBBienChe::Xuat()
{
	cout << "Can bo " << Loai <<'.';
	cout << "\nMa so: " << MaSo;
	cout << "\nHo va ten can bo: " << HoTen;
	cout << "\nLuong: " <<TinhLuong();
	cout << "\nLuong co ban cua can bo bien che: " << LuongCoBan;
	cout << "\nHe so luong cua can bo bien che: " << HeSoLuong;
	cout << "\nHe so phu cap: " << HeSoPhuCap;
}