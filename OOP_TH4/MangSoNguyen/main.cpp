#include<iostream>
#include"MangSoNguyen.h"
#include"algorithm"
#include"cmath"
using namespace std;

istream& operator>>(istream&, MangSoNguyen&);
ostream& operator<<(ostream&, MangSoNguyen&);
int main()
{
	MangSoNguyen a, b,Sum;
	cin >> a >> b;
	cout <<"\nMang so nguyen a: " << a << '\n';
	cout <<"Mang so nguyen b: " << b << '\n';

	Sum =a+b;
	cout << "a+b= " << Sum << '\n';

	MangSoNguyen c, d;
	c = Sum++;
	d = ++Sum;
	cout << "Sum++: " << c << '\n';
	cout << "++Sum: " << d;

}
istream& operator>>(istream&is, MangSoNguyen&iArray)
{
	cout << "Nhap so phan tu mang so nguyen: ";
	is >> iArray.kichthuoc;

	iArray.dulieu = new int[iArray.kichthuoc];
	for (int i = 0; i < iArray.kichthuoc; i++)
	{
		cout << "\nNhap phan tu tai vi tri thu " << i << " : ";
		is >> iArray.dulieu[i];
	}
	return is;
}
ostream& operator<<(ostream&os, MangSoNguyen&iArray)
{
	for (int i = 0; i < iArray.kichthuoc; i++)
		os << iArray.dulieu[i] <<'\t';
	return os;
}