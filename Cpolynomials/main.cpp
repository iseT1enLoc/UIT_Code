#include "DaThuc.h"
#include <iostream>
using namespace std;
int main()
{
	DaThuc a,b;
	float x;
	a.Nhap();
	a.XuatSoMuGiamDan();
	cout << endl;
	b.Nhap();
	b.XuatSoMuGiamDan();
	cout << endl;
	cout << "\nNhap x: dathuc a!"; cin >> x;
	cout << "\nGia Tri da thuc a tai x= " << x << " la: " << a.TinhGiaTriDaThucTaiX(x);
	cout << "\nKet qua phep cong hai da thuc: "; a.Cong(b).XuatSoMuGiamDan();
	cout << "\nKet qua phep tru hai da thuc: "; a.Tru(b).XuatSoMuGiamDan();
}