#pragma once
#include"MONHOC.h"
using namespace std;

class MONKIEMTRA :public MONHOC
{
protected:
	float HeSo3;
public:
	MONKIEMTRA();
	MONKIEMTRA(string, string, float, float, float, float);
	~MONKIEMTRA();

	/*friend istream operator>>(istream&, MONKIEMTRA&) ;
	friend ostream operator<<(ostream&, MONKIEMTRA&) ;*/

	void Nhap();
	void Xuat();

	float LayDiemKTHetMon();
	void CapNhatDiemKTHetMon(float);

	float TinhDiemKetThucMonHoc();
};