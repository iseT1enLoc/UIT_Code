#pragma once
#include"GiaSuc.h"
class De :public GiaSuc
{
public:
	static int qDe;
	De()
	{
		Ten = "De";
		++qDe;
	}
	void TiengKeu();
	int ChoSua();
	int SinhCon();
	string ten();
};