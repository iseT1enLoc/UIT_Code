#pragma once
#include"NhanVien.h"

class NhanVienVanPhong:public NhanVien
{
protected:
	int LopThamDu;
	float GioLD;//so gio tham gia lao dong cong ich
public:
	NhanVienVanPhong()
	{
		Loai = "Nhan vien van phong";
	}
	void Nhap();
	void Xuat();
	bool DuTieuChuan();
};