#include<iostream>
#include"SoPhuc.h"
using namespace std;
istream& operator>>(istream&, SoPhuc&);
ostream& operator<<(ostream&, const SoPhuc&);

int main()
{
	SoPhuc a, b, Sum, Sub, Multi, Div;

	cin >> a >> b;
	cout <<"So Phuc a : "<< a << '\n';
	
	cout <<"So Phuc b: "<< b << '\n';

	Sum = a + b;
	Sub = a - b;
	Multi = a * b;
	Div = a / b;

	cout << "a+b= " << Sum << '\n';
	cout << "a-b= " << Sub << '\n';
	cout << "a*b= " << Multi << '\n';
	cout << "a/b= " << Div << '\n';

	if (a != b)
		cout << "a1!=b";
	else
		cout << "a==b";
}


istream& operator>>(istream&is, SoPhuc& SPhuc)
{
	cout << "Nhap phan thuc: ";
	is >> SPhuc.thuc;
	cout << "Nhap phan ao: ";
	is >> SPhuc.ao;
	return is;
}
ostream& operator<<(ostream& os, const SoPhuc& SPhuc)
{
	if (SPhuc.thuc == 0) {
		os << SPhuc.ao << "i";
	}
	else if (SPhuc.ao == 0) {
		os << SPhuc.thuc;
	}
	else {
		if (SPhuc.ao < 0) {
			os << SPhuc.thuc << SPhuc.ao << "i";
		}
		else if (SPhuc.ao > 0) {
			os << SPhuc.thuc << "+" << SPhuc.ao << "i";
		}
	}
	return os;
}