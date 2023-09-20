#pragma once
#include"CanBo.h"
class CBHopDong :public CanBo
{
protected:
	float TienCong;
	int SoNgayCong;
	float HeSoVuotGio;
public:
	CBHopDong()
	{
		Loai = "Hop Dong";
	}
	void Nhap();
	void Xuat();
	float TinhLuong();
};