#pragma once
#include"MONHOC.h"
#include<vector>
class DANHSACHMONHOC
{
protected:
	int n;
	vector<MONHOC*>List;
public:
	DANHSACHMONHOC()
	{

	}
	int LayTongSoMonHoc()
	{
		return n;
	}

	friend istream& operator>>(istream&, DANHSACHMONHOC&);
	friend ostream& operator<<(ostream&, DANHSACHMONHOC&);

	float DTBHK();
	string MonHocCoDiemTongKetCaoNhat();

};