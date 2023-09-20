#pragma once
#include"NhanSu.h"
#include<string>
using namespace std;
class CGiangVien :public CNhanSu
{
protected:
	string sHocHam;
	string sHocVi;
	float fExGiangDay;
	vector<string*>vMonHoc;
public:
	void Nhap();
	void Xuat();
	double TinhLuong();
};
