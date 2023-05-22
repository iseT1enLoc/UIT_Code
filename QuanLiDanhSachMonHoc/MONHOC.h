#pragma once
#include<string>
using namespace std;

class MONHOC
{
protected:
	int loai;
	string MaSo;
	string TenMonHoc;
	float HeSoMonHoc;
	float HeSo1;
	float HeSo2;
public:
	MONHOC();
	MONHOC(string, string, float,float,float);

	//friend virtual istream operator>>(istream&,MONHOC&)=0;
	//friend virtual ostream operator<<(ostream&, MONHOC&) = 0;
	virtual void Nhap()=0;
	virtual void Xuat()=0;


	int LayLoai();
	float LayHeSoMonHoc();
	string LayMaSo();
    void CapNhatMaSo(string);

	string LayTenMonHoc();
	void CapNhatTenMonHoc(string);

	float LayHeSo1();
	void CapNhatHeSo1(float);

	float LayHeSo2();
	void CapNhatHeSo2(float);

	virtual float TinhDiemKetThucMonHoc() = 0;


};