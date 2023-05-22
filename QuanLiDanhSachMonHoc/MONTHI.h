#pragma once
#include"MONHOC.h"

class MONTHI :public MONHOC
{
protected:
	float DiemThiHetMon;
public:
	MONTHI();
	MONTHI(string,string,float,float,float,float);
	~MONTHI();

	void Nhap();
	void Xuat();

	float LayDiemThiHetMon();
	void CapNhatDiemThiHetMon(float);

	float DiemTrungBinhKiemTra();

	float TinhDiemKetThucMonHoc();
};