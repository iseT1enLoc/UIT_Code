#pragma once
#include"GiaSuc.h"
class NongTrai
{
protected:
	int tong;
	GiaSuc* ds[100000];
public:
	void Nhap();
	void SinhSan();
	void TiengKeuONongTrai();
	int TongLitSua();
};