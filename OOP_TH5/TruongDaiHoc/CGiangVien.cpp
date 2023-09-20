#include"CGiangVien.h"
#include<iostream>
#include<string>
using namespace std;

class NhanSu;
void CGiangVien::Nhap()
{
	cout << "Nhap ho ten: ";
	getline(cin, sHoTen);
	cout << "Nhap ngay/thang/nam sinh: ";
	getline(cin, sNgaySinh);
	cout << "Nhap ma so giang vien: ";
	getline(cin, sMaSo);
	cout << "Nhap hoc ham: ";
	getline(cin, sHocHam);
	cout << "Nhap hoc vi: ";
	getline(cin, sHocVi);
	cout << "Nhap so nam giang day: ";
	cin >> fExGiangDay;
	cout << "So mon hoc giang day: ";
	int temp;
	cin >> temp;
	for (int i = 0; i < temp; i++)
	{
		cout << "Mon hoc thu " << i + 1 << " : ";
		string* Ten;
		getline(cin, *Ten);
		vMonHoc.push_back(Ten);
	}
}
void CGiangVien::Xuat()
{
	cout << "Ten giang vien: " << sHoTen;
	cout << "\nNgay/Thang/Nam sinh: " << sNgaySinh;
	cout << "\nMa so giang vien: " << sMaSo;
	cout << "\nHoc ham: " << sHocHam;
	cout << "\nHoc vi: " << sHocVi;
	cout << "\nCac mon hoc giang day la: ";
	int count = 1;
	for (auto m : vMonHoc)
	{
		cout << "\nMon hoc thu " << count++ << *m;
	}
}
double CGiangVien::TinhLuong()
{
	return vMonHoc.size() * fExGiangDay * 0.12 * 20000;
}