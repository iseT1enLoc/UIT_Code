#pragma once
#include"NhanVien.h"
class NghienCuuVien:public NhanVien
{
protected:
	int DeTaiTG;//so de tai nghien cuu ma nghien cuu vien dang tham gia
	int BaoKH;// so bai bao khoa hoc ma nghien cuu vien do la tac gia hoac dong tac gia
public:
	NghienCuuVien()
	{
		Loai = "Nghien cuu vien";
	}
	void Nhap();
	void Xuat();
	bool DuTieuChuan();
};