#include"CongTy.h"
#include<iostream>
using namespace std;

int main()
{
	CongTy UIT;
	UIT.Nhap();
	cout << "\nTHONG TIN CUA CAN BO TRONG CONG TY: \n";
	UIT.Xuat();
	cout << "Tong luong cua cong ty " << UIT.LayTen() << " la: " << UIT.TinhTongLuong();
}
