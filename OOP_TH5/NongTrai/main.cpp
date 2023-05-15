#include "NongTrai.h"
#include"Bo.h"
#include"Cuu.h"
#include"De.h"
#include<iostream>
using namespace std;


int main()
{
	NongTrai A;
	A.Nhap();
	A.SinhSan();
	cout << '\n';
	A.TiengKeuONongTrai();
	cout << "Tong so lit sua thu duoc: " << A.TongLitSua() << " lit;";
}