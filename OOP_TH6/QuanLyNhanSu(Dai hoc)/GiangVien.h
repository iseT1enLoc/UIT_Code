#pragma once
#include"NhanVien.h"
class GiangVien:public NhanVien
{
protected:
	int SoTiet;
	int SoDeTaiKL;//so de tai khoa luan ma giang vien huong dan
public:
	GiangVien()
	{
		Loai = "Giang vien";
	}
	void Nhap();
	void Xuat();
	bool DuTieuChuan();
};