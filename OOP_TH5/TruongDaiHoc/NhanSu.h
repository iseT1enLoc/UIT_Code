#pragma once
#include<string>
#include<vector>

class CNhanSu
{
protected:
	string sHoTen;
	string sNgaySinh;
	string sMaSo;
public:
	virtual void Nhap();
	virtual void Xuat();
	virtual double TinhLuong();
};
