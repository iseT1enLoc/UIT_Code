#pragma once
#include<string>
using namespace std;
class CanBo
{
protected:
	string Loai;
	string MaSo;
	string HoTen;
	string NgaySinh;
	float Luong;
public:
	virtual void Nhap() = 0;
	virtual void Xuat() = 0;
	virtual float TinhLuong() = 0;
};