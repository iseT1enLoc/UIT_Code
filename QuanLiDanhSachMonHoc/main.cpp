#include<iostream>
#include"DANHSACHMONHOC.h"
using namespace std;

int main()
{
	DANHSACHMONHOC A;
	cin >> A;
	cout << A;
	cout << "\nMon hoc co diem tong ket cao nhat: " << A.MonHocCoDiemTongKetCaoNhat();
	cout << "\nDiem trung binh hoc ki: "<<A.DTBHK();
}