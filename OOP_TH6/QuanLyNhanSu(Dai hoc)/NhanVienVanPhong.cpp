#include"NhanVienVanPhong.h"
#include<iostream>
using namespace std;

void NhanVienVanPhong::Nhap()
{
	cout << "Nhap ma so nhan vien van phong: ";
	getline(cin, MaSo);
	cout << "Nhap ho va ten nhan vien van phong: ";
	getline(cin, HoTen);
	cout << "Nhap ngay thang nam sinh nhan vien van phong: ";
	getline(cin, NgaySinh);
	cout << "Nhap so luong lop boi duong chuyen mon ma nhan vien da tham du trong nam: ";
	cin >> LopThamDu;
	cout << "Nhap so gio lao dong cong ich do truong to chuc cua nhan vien tren: ";
	cin >> GioLD;
}
void NhanVienVanPhong::Xuat()
{
	cout << "Ma so nhan vien van phong: " << MaSo;
	cout << "\nHo va ten nhan vien van phong: " << HoTen;
	cout << "\nNgay thang nam sinh: " << NgaySinh;
	cout << "\nSo luong lop boi duong chuyen mon ma nhan vien da tham du trong nam: "<<LopThamDu;
	cout << "\nSo gio lao dong cong ich do truong to chuc cua nhan vien tren: " << GioLD;
}
bool NhanVienVanPhong::DuTieuChuan()
{
	return LopThamDu >= 1 && GioLD >= 20;
}
