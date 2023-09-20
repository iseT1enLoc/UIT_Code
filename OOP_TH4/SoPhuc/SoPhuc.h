#pragma once
#include<iostream>
using namespace std;
class SoPhuc
{
private:
	float thuc;
	float ao;
public:
	SoPhuc();
	SoPhuc(const SoPhuc&);

	SoPhuc operator+(const SoPhuc&)const;
	SoPhuc operator-(const SoPhuc&)const;
	SoPhuc operator*(const SoPhuc&)const;
	SoPhuc operator/(const SoPhuc&)const;

	bool operator==(const SoPhuc&);
	bool operator!=(const SoPhuc&);
	friend istream& operator>>(istream&, SoPhuc&);
	friend ostream& operator<<(ostream&, const SoPhuc&);

};