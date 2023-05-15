#pragma once
#include<iostream>
using namespace std;
class MangSoNguyen
{
private:
	int* dulieu;//con tro tro den mot mang dong kieu so nguyen
	int kichthuoc;//bien chua kich thuoc cua mang so nguyen
public:
	MangSoNguyen();
	MangSoNguyen(int, int);
	MangSoNguyen(int);

	~MangSoNguyen();

	MangSoNguyen& operator=(const MangSoNguyen&);
	MangSoNguyen operator+(const MangSoNguyen&);
	bool operator==(const MangSoNguyen&);
	MangSoNguyen&operator++();//toan tu tien to
	MangSoNguyen operator++(int);//toan tu hau to;


	int LayKichThuoc();

	friend istream& operator>>(istream&, MangSoNguyen&);
	friend ostream& operator<<(ostream&, MangSoNguyen&);


};