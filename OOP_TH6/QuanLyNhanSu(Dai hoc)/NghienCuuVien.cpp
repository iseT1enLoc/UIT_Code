#include"NghienCuuVien.h"
#include<iostream>
using namespace std;

void NghienCuuVien::Nhap()
{
	cout << "Nhap ma so nghien cuu vien: ";
	getline(cin, MaSo);
	cout << "Nhap ho va ten nghien cuu vien: ";
	getline(cin, HoTen);
	cout << "Nhap ngay thang nam sinh nghien cuu vien: ";
	getline(cin, NgaySinh);
	cout << "Nhap so de tai nghien cuu ma nghien cuu vien tham gia: ";
	cin >> DeTaiTG;
	cout << "Nhap so bai bao khoa hoc ma nghien cuu vien la tac gia(hoac dong tac gia): ";
	cin >> BaoKH;
}
void NghienCuuVien::Xuat()
{
	cout << "Ma so nghien cuu vien: " << MaSo;
	cout << "\nHo va ten nghien cuu vien: " << HoTen;
	cout << "\nNgay thang nam sinh: " << NgaySinh;
	cout << "\nSo de tai nghien cuu ma nghien cuu vien tham gia: " << DeTaiTG;
	cout << "\nSo bai bao khoa hoc ma nghien cuu vien la tac gia (hoac dong tac gia): " << BaoKH;
}
bool NghienCuuVien::DuTieuChuan()
{
	return DeTaiTG >= 1 && BaoKH >= 2;
}
