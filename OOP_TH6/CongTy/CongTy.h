#pragma once
#include"CanBo.h"
#include"CBBienChe.h"
#include"CBHopDong.h"
#include"CongTy.h"

class CongTy
{
protected:
	string Ten;
	int tong;//tong so can bo trong cong ty;
	CanBo* ds[10000];
public:
	void Nhap();
	void Xuat();
	string LayTen();
	double TinhTongLuong();
};