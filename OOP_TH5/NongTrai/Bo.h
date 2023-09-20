#pragma once
#include"GiaSuc.h"
class Bo:public GiaSuc
{
public:
	static int qBo;
	Bo()
	{
		Ten = "Bo";
		++qBo;
	}
	void TiengKeu();
	int ChoSua();
	int SinhCon();
	string ten();
};