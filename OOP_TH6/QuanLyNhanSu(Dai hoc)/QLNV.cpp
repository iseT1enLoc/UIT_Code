#include"QLNV.h"
#include<iostream>
using namespace std;

istream& operator>>(istream& is, QLNV& a)
{
	cout << "Nhap vao so luong nhan vien cua truong dai hoc K: ";
	is >> a.n;
	for (int i = 0; i < a.n; ++i)
	{
		cout << "Nhap thong tin nhan vien(1.Giang vien,2.Nghien cuu vien,3.Nhan vien van phong): ";
		int luachon;
		cin >> luachon;
		switch (luachon)
		{
		case 1:
			a.ds[i] = new GiangVien;
			break;
		case 2:
			a.ds[i] = new NghienCuuVien;
			break;
		case 3:
			a.ds[i] = new NhanVienVanPhong;
			break;
		}
		cin.ignore();
		a.ds[i]->Nhap();
		cout << '\n';
	}
	return is;
}
ostream& operator<<(ostream& os, QLNV& a)
{
	for (int i = 0; i < a.n; ++i)
	{
		a.ds[i]->Xuat();
		cout << '\n';
	}
	return os;
}
void QLNV::NhanVienLaoDongTienTien()
{
	for (int i = 0; i < n; ++i)
	{
		if (ds[i]->DuTieuChuan())
		{
			cout << ds[i]->LayTen() << '\n';
		}
	}
}