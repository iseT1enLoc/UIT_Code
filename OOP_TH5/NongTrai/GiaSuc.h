#pragma once
#include<string>
using namespace std;
class GiaSuc
{
protected:
	string Ten;
public:
	static int qGiaSuc;
	GiaSuc()
	{
		++qGiaSuc;
	}
	virtual void TiengKeu();
	virtual int ChoSua();
	virtual int SinhCon();
	virtual string ten();
};