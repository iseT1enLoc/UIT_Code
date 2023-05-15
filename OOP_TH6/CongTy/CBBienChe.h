#pragma once
#include"CanBo.h"
class CBBienChe :public CanBo
{
protected:
	float LuongCoBan;
	float HeSoLuong;
	float HeSoPhuCap;
public:
	CBBienChe()
	{
		Loai = "Bien Che";
	}
	void Nhap();
	void Xuat();
	float TinhLuong();
};