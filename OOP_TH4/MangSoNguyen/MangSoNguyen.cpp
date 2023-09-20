#include"MangSoNguyen.h"
using namespace std;

MangSoNguyen::MangSoNguyen()
{
	
}
MangSoNguyen::MangSoNguyen(int n, int x)//khoi tao mang co n phan tu gia tri bang x
{
	kichthuoc = n;
	dulieu = new int[kichthuoc];

	for (int i = 0; i < n; i++) dulieu[i] = x;
}
MangSoNguyen::MangSoNguyen(int n)
{
	kichthuoc = n;
	dulieu = new int[n];
}

MangSoNguyen::~MangSoNguyen()
{
	//delete[]dulieu;
	//dulieu = nullptr;
}
bool MangSoNguyen::operator==(const MangSoNguyen& other)
{
	if (kichthuoc == other.kichthuoc)
	{
		for (int i = 0; i < kichthuoc; i++)
		{
			if (dulieu[i] == other.dulieu[i]) continue;
			else
				return false;
		}
		return true;
	}
	else return false;
}

MangSoNguyen& MangSoNguyen::operator=(const MangSoNguyen&other)
{
	kichthuoc = other.kichthuoc;

	dulieu = new int[kichthuoc];

	for (int i = 0; i < kichthuoc; i++)
	{
		dulieu[i] = other.dulieu[i];
	}
	return *this;
}
int MangSoNguyen::LayKichThuoc()
{
	return kichthuoc;
}
MangSoNguyen MangSoNguyen::operator+(const MangSoNguyen&other)
{
	int KThuoc = (this->kichthuoc > other.kichthuoc) ? this->kichthuoc : other.kichthuoc;

	MangSoNguyen Tong(KThuoc);
	
	int kq = 0;//Tong
	int i = 0;//this
	int j = 0;//other

	for (kq = 0; i < kichthuoc && j < other.kichthuoc;kq++)
	{
		Tong.dulieu[kq] = dulieu[i++] + other.dulieu[j++];
	}

	while (i < kichthuoc)
	{
		Tong.dulieu[kq++] = dulieu[i++];
	}
	while (j < other.kichthuoc)
	{
		Tong.dulieu[kq++] = other.dulieu[j++];
	}

	return Tong;
}
MangSoNguyen& MangSoNguyen::operator++()
{
	for (int i = 0; i < kichthuoc; i++)
		++dulieu[i];
	return *this;
}
MangSoNguyen MangSoNguyen::operator++(int x)
{
	MangSoNguyen KetQua;
	KetQua = *this;
	for (int i = 0; i < kichthuoc; i++)
		dulieu[i]++;
	return KetQua;
}
