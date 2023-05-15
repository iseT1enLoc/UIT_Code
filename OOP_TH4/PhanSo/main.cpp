#include<iostream>
#include"PhanSo.h"
using namespace std;

istream& operator>>(istream&, PhanSo&);
ostream& operator<<(ostream&, const PhanSo&);
int main()
{
	PhanSo a, b, sum, sub, multi, dev;
	cin >> a >> b;
	cout << a << endl;
	cout << b << endl;

	sum = a + b;
	sub = a - b;
	multi = a * b;
	dev = a / b;

	cout << "\na+b= " << sum;
	cout << "\na-b= " << sub;
	cout << "\na*b= " << multi;
	cout << "\na/b= " << dev;

	sum += a;
	sub += b;
	multi += a;
	dev += b;
	cout << "\n";
	cout << "\nsum+=a: " << sum;
	cout << "\nsub+=b : "<< sub;
	cout << "\nmulti+=a: " << multi;
	cout << "\ndev/=b: " << dev;

	if (sum == sub)
		cout << "\nTong bang hieu.";
	else cout << "\nTong khong bang hieu.";

	if (sum < sub)
		cout << "\nTong nho hon hieu.";
	else cout << "\nTong khong nho hon hieu.";

	if (sum <= sub)
		cout << "\nTong nho hon hoac bang hieu.";
	else cout << "\nTong khong nho hon hoac ban hieu.";

	if(sum>=sub)
		cout << "\nTong lon hon hoac bang hieu.";
	else cout << "\nTong khong lon hon hoac ban hieu.";


}
istream& operator>>(istream& is, PhanSo&ps)
{
	cout << "Nhap tu so: ";
	is >> *ps.tuso;
	cout << "Nhap mau so: ";
	is >> *ps.mauso;
	return is;
}
ostream& operator<<(ostream& os,const PhanSo& ps)
{
	if (*ps.tuso % *ps.mauso == 0)
	{
		os<<*ps.tuso/(*ps.mauso);
	}
	else
	{
		os<< *ps.tuso << "/" << *ps.mauso;
	}
	return os;
}
