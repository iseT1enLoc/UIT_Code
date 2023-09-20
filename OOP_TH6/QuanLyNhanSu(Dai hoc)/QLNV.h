#pragma once
#include"NhanVien.h"
#include"GiangVien.h"
#include"NghienCuuVien.h"
#include"NhanVienVanPhong.h"

class QLNV
{
protected:
	int n;//tong so nhan vien;
	NhanVien* ds[1000];
public:

	friend istream& operator>>(istream&,QLNV&);
	friend ostream& operator<<(ostream&,QLNV&);
	void NhanVienLaoDongTienTien();
};