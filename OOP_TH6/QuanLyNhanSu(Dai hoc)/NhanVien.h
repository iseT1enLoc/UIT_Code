#pragma once
#include<string>
using namespace std;
class NhanVien
{
protected:
	string MaSo;
	string HoTen;
	string NgaySinh;
	string Loai;//1-Giangvien,2-Nghien cuu vien,3-Nhan vien van phong
public:
	virtual void Nhap() = 0;
	virtual void Xuat() = 0;
	virtual bool DuTieuChuan() = 0;
	string LayTen()
	{
		return HoTen;
	}
};