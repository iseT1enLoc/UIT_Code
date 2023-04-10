#pragma once
#include "DonThuc.h"
class DaThuc
{
private:
	int n;//So luong don thuc trong da thuc;
	DonThuc* DSDonThuc;
public:
	//Chuong trinh cho phep thuc hien phep tinh khi nhap hai da thuc voi so mu khong theo chieu co dinh
	//nen phan xuat da thuc co hai loai la XuatGiuNguyen va XuatSoMuGiamDan
	void Nhap();
	DaThuc();
	DaThuc(int);
	~DaThuc();
	DaThuc(const DaThuc&);
	void XuatSoMuGiamDan();
	void XuatGiuNguyen();
	int LaySoLuongDonThuc();
	void GanSoLuongDonThuc(int);
	DaThuc Cong(DaThuc);
	DaThuc Tru(DaThuc);
	double TinhGiaTriDaThucTaiX(float);
};