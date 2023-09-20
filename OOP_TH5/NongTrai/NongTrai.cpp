#include"NongTrai.h"
#include<iostream>
#include"Bo.h"
#include"Cuu.h"
#include"De.h"

int Bo::qBo = 0;
int Cuu::qCuu = 0;
int De::qDe = 0;
int GiaSuc::qGiaSuc = 0;
void NongTrai::Nhap()
{
	int numBo, numCuu, numDe;
	cout << "Nhap vao so luong bo: ";
	cin >> numBo;
	cout << "Nhap vao so luong cuu: ";
	cin >> numCuu;
	cout << "Nhap vao so luong de: ";
	cin >> numDe;

    tong = numCuu + numBo + numDe;
	for (int i = 0; i < numBo; ++i)
	{
		ds[i] = new Bo;
	}

	for (int j = numBo; j < numBo + numCuu; ++j)
	{
		ds[j] = new Cuu;
	}
	for (int k = numBo + numCuu; k < tong; ++k)
	{
		ds[k] = new De;
	}
}
void NongTrai::SinhSan()
{
	int Sum = 0;
	int soBo = 0, soCuu = 0, soDe = 0;
	for (int i = 0; i < tong; ++i)
	{
		if (ds[i]->ten() == "Bo") soBo += ds[i]->SinhCon();
		else if (ds[i]->ten() == "De") soDe += ds[i]->SinhCon();
		else if (ds[i]->ten() == "Cuu") soCuu += ds[i]->SinhCon();
		Sum+=ds[i]->SinhCon();
	}
	cout << "\nSo luong gia suc sau mua sinh san la: " << Sum;
	cout << "\nSo cuu cua nong trai sau khi sinh san: " << Cuu::qCuu + soCuu;
	cout << "\nSo bo cua nong trai sau khi sinh san: " << Bo::qBo + soBo;
	cout << "\nSo de cua nong trai sau khi sinh san: " << De::qDe + soDe;
}
void NongTrai::TiengKeuONongTrai()
{
	for (int i = 0; i < tong; ++i)
	{
		ds[i]->TiengKeu();
		cout << '\n';
	}
}
int NongTrai::TongLitSua()
{
	int sum = 0;
	for (int i = 0; i < tong; ++i)
	{
		sum += ds[i]->ChoSua();
	}
	return sum;
}