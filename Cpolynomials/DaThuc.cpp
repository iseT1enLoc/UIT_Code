#include "DaThuc.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
using namespace std;
DaThuc::DaThuc()
{
	n = 1;
	DSDonThuc = new DonThuc[1];
	DSDonThuc->GanSoMu(0);
}
DaThuc::DaThuc(int n)
{
	this->n = n;
	DSDonThuc = new DonThuc[n];
}
DaThuc::DaThuc(const DaThuc& other)
{
	n = other.n;
	DSDonThuc = new DonThuc[n];
	for (int i = n - 1; i >= 0; i--)
	{
		DSDonThuc[i].GanSoMu(other.DSDonThuc[i].LaySoMu());
		DSDonThuc[i].GanHeSo(other.DSDonThuc[i].LayHeSo());
	}
}
DaThuc::~DaThuc()
{
	delete[]DSDonThuc;
	DSDonThuc = NULL;
}
void DaThuc::Nhap()
{
	cout << "\nNhap so luong don thuc trong da thuc: ";
	cin >> n;
	DSDonThuc = new DonThuc[n];
	for (int i = n-1; i >0; i--)
	{
		DSDonThuc[i].Nhap();
	}
	cout << "\nNhap don thuc cuoi cung: ";
	DSDonThuc[0].Nhap();
}
void DaThuc::XuatGiuNguyen()
{
	bool OK = 0;
	double s = 0;
	for (int i = n-1; i >=0;--i)
	{
		s += DSDonThuc[i].LayHeSo();
		if (DSDonThuc[i].LayHeSo() == 0) continue;
		if (OK)
		{
			if (DSDonThuc[i].LayHeSo() > 0) cout << "+";
		}
		if (DSDonThuc[i].LaySoMu() != 1 &&DSDonThuc[i].LaySoMu() != 0) {
			if (DSDonThuc[i].LayHeSo() == 1) cout << "x^" << DSDonThuc[i].LaySoMu();
			else if (DSDonThuc[i].LayHeSo() == -1) cout << "-x^" <<DSDonThuc[i].LaySoMu();
			else cout << DSDonThuc[i].LayHeSo() << "x^" << DSDonThuc[i].LaySoMu();
			OK = 1;
		}
		if (DSDonThuc[i].LaySoMu() == 1) {
			if (DSDonThuc[i].LayHeSo() == 1) cout << "x";
			else if (DSDonThuc[i].LayHeSo() == -1) cout << "-x";
			else cout << DSDonThuc[i].LayHeSo()<< "x";
			OK = 1;
		}
		if (DSDonThuc[i].LaySoMu() == 0)
		{
			if (DSDonThuc[i].LayHeSo() == 1) cout << 1;
			else if (DSDonThuc[i].LayHeSo() == -1) cout << -1;
			else cout << DSDonThuc[i].LayHeSo();
			OK = 1;
		}
	}
	if (s == 0) cout << 0;
}
void DaThuc::XuatSoMuGiamDan()
{
	//su dung map voi muc dich dua cac so mu lon ve dau tao dieu kien cho viec XuatGiuNguyen.
	map<int, float,greater<int>>mp;
	for (int i = 0; i < n; i++)
	{
		mp.insert({ DSDonThuc[i].LaySoMu(),DSDonThuc[i].LayHeSo() });
	}
	int dem = n - 1;//de quan li so phan tu trong list don thuc;
	for (auto it = mp.begin(); it != mp.end(); it++)
	{
		DSDonThuc[dem].GanHeSo((*it).second);
		DSDonThuc[dem].GanSoMu((*it).first);
		dem--;
	}
	XuatGiuNguyen();
}
int DaThuc::LaySoLuongDonThuc()
{
	return n;
}
void DaThuc::GanSoLuongDonThuc(int n)
{
	this->n = n;
}
DaThuc DaThuc::Cong(DaThuc other)
{
	multimap<int, float>mp;
	set<int>se;
	//su dung multimap voi muc dich de cac so mu bang nhau lai gan nhau tao dieu kien cho viec
	//truy xuat cac phan tu khi cong
	//set dung de loc ra cac so mu khac nhau trong da thuc ket qua
	for (int i = 0; i < n; i++) {
		mp.insert({ DSDonThuc[i].LaySoMu(),DSDonThuc[i].LayHeSo()});
		se.insert({ DSDonThuc[i].LaySoMu()});
	}
	for (int i = 0; i < other.LaySoLuongDonThuc(); i++) {
		mp.insert({ other.DSDonThuc[i].LaySoMu(),other.DSDonThuc[i].LayHeSo()});
		se.insert({ other.DSDonThuc[i].LaySoMu()});
	}
	auto s = se.size();
	DaThuc Tong(s);//Tao da thuc cong voi s phan tu
	auto dem = se.begin();
	int kq = 0;
	int mu = 0;
	for (auto m : se)
	{
		Tong.DSDonThuc[mu].GanSoMu(m);
		Tong.DSDonThuc[mu].GanHeSo(0);
		mu++;
	}
	for (auto it = mp.begin(); it != mp.end(); it++)
	{
		if ((*it).first == (*dem))
		{
			float temp = Tong.DSDonThuc[kq].LayHeSo() + (*it).second;
			Tong.DSDonThuc[kq].GanHeSo(temp);
		}
		else
		{
			kq++;
			dem++;
			float temp = Tong.DSDonThuc[kq].LayHeSo() + (*it).second;
			Tong.DSDonThuc[kq].GanHeSo(temp);
		}

	}
	return Tong;
}
DaThuc DaThuc::Tru(DaThuc other)
{
	//lan luot nhan -1 cho da thuc other roi thuc hien phep cong nhu cu.
	for (int i = 0; i < other.LaySoLuongDonThuc(); i++)
	{
		float temp = -1*other.DSDonThuc[i].LayHeSo();
		other.DSDonThuc[i].GanHeSo(temp);
	}
	return Cong(other);
}
double DaThuc::TinhGiaTriDaThucTaiX(float x)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + DSDonThuc[i].LayHeSo() * pow(x, DSDonThuc[i].LaySoMu());
	}
	return sum;
}

