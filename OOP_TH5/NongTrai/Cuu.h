#pragma once
#include"GiaSuc.h"
class Cuu :public GiaSuc
{
public:
	static int qCuu;
	Cuu()
	{
		Ten = "Cuu";
		++qCuu;
	}
	void TiengKeu();
	int ChoSua();
	int SinhCon();
	string ten();
};