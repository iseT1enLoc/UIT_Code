#pragma once
#include<iostream>
using namespace std;
class PhanSo
{
private:
	int* tuso;
	int* mauso;
public:
	PhanSo();
	//~PhanSo();
	PhanSo(const PhanSo&);
	PhanSo(int, int);

	PhanSo& operator=(const PhanSo&);

	PhanSo operator+(const PhanSo&);
	PhanSo operator-(const PhanSo&);
	PhanSo operator*(const PhanSo&);
	PhanSo operator/(const PhanSo&);

	PhanSo& operator+=(const PhanSo&);
	PhanSo& operator-=(const PhanSo&);
	PhanSo& operator*=(const PhanSo&);
	PhanSo& operator/=(const PhanSo&);

	bool operator==(const PhanSo&);
	bool operator<(const PhanSo&);
	bool operator>(const PhanSo&);
	bool operator<=(const PhanSo&);
	bool operator>=(const PhanSo&);
	bool operator!=(const PhanSo&&);

	//toan tu hau to ps++
	PhanSo operator++(int);
	//toan tu tien to ++ps;
	PhanSo& operator++();

	//toan tu hau to ps--
	PhanSo operator--(int);
	//toan tu tien to ++ps;
	PhanSo& operator--();
	friend istream& operator>>(istream&, PhanSo&);
	friend ostream& operator<<(ostream&,const PhanSo&);
};