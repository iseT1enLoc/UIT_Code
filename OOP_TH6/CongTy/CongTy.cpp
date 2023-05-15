#include"CongTy.h"
#include<iostream>
using namespace std;

void CongTy::Nhap()
{
	cout << "Nhap vao ten cong ty: ";
	getline(cin, Ten);
	cout << "Nhap vao so luong can bo trong cong ty: ";
	cin >> tong;
	for (int i = 0; i < tong; ++i)
	{
		int luachon;
		cout << "Nhap vao can bo(0.Can bo bien che,1.Can bo hop dong)";
		cin >> luachon;
		switch (luachon)
		{
		case 0:
			ds[i] = new CBBienChe;
			break;
		case 1:
			ds[i] = new CBHopDong;
			break;
		}
		cin.ignore();
		ds[i]->Nhap();
		cout << '\n';
	}
}
void CongTy::Xuat()
{
	for (int i = 0; i < tong; ++i)
	{
		ds[i]->Xuat();
		cout << '\n';
	}
}
string CongTy::LayTen()
{
	return Ten;
}
double CongTy::TinhTongLuong()
{
	double KetQua = 0;
	for(int i=0;i<tong;++i)
	{
		KetQua += ds[i]->TinhLuong();
	}
	return KetQua;
}