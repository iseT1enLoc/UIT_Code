#include"DANHSACHMONHOC.h"
#include"MONKIEMTRA.h"
#include"MONTHI.h"
#include<algorithm>
#include<iostream>
using namespace std;
istream& operator>>(istream&is, DANHSACHMONHOC& ds)
{
	cout << "Nhap vao tong so mon hoc: ";
	is >> ds.n;
	for (int i = 0; i < ds.n; ++i)
	{
		cout << "Nhap vao loai mon hoc(1.Mon kiem tra-2.Mon thi)";
		int opt;
		cin >> opt;
		cin.ignore();
		switch (opt)
		{
		case 1:
			ds.List.push_back(new MONKIEMTRA);
			break;
		case 2:
			ds.List.push_back(new MONTHI);
			break;
		}
		ds.List[i]->Nhap();
		cout << '\n';
	}
	return is;
}
ostream& operator<<(ostream& os,DANHSACHMONHOC& ds)
{
	for (int i = 0; i < ds.n; ++i)
	{
		ds.List[i]->Xuat();
		os<< '\n';
	}
	return os;
}

float DANHSACHMONHOC::DTBHK()
{
	float Tong = 0;
	float TongHeSo=0;
	for (int i = 0; i < n; ++i)
	{
		if (List[i]->LayLoai() == 1)
		{
			Tong += List[i]->LayHeSoMonHoc() * List[i]->TinhDiemKetThucMonHoc();
			TongHeSo += List[i]->LayHeSoMonHoc();
		}
		else
		{
			Tong += (2*List[i]->LayHeSoMonHoc() * List[i]->TinhDiemKetThucMonHoc());
			TongHeSo += (2*List[i]->LayHeSoMonHoc());
		}
	}
	return Tong / TongHeSo;
}
bool cmp(MONHOC* a, MONHOC* b)
{
	return a->TinhDiemKetThucMonHoc() > b->TinhDiemKetThucMonHoc();
}
string DANHSACHMONHOC::MonHocCoDiemTongKetCaoNhat()
{
	sort(List.begin(), List.end(),cmp);
	
	return List[0]->LayTenMonHoc();
}