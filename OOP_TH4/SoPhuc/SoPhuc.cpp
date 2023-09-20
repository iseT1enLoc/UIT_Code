#include "SoPhuc.h"
#include<iostream>
#include<cmath>
using namespace std;

SoPhuc::SoPhuc()
{

}

SoPhuc::SoPhuc(const SoPhuc&other)
{
	this->thuc = other.thuc;
	this->ao = other.ao;
}
SoPhuc SoPhuc::operator+(const SoPhuc &other)const {
	SoPhuc kq;
	kq.thuc = thuc + other.thuc;
	kq.ao = ao + other.ao;
	return kq;
}
SoPhuc SoPhuc::operator-(const SoPhuc &other)const {
	SoPhuc kq;
	kq.thuc = thuc - other.thuc;
	kq.ao = ao - other.ao;
	return kq;
}
SoPhuc SoPhuc::operator*(const SoPhuc &other) const{
	SoPhuc kq;
	kq.thuc = thuc * other.thuc - ao * other.ao;
	kq.ao = thuc * other.ao + ao * other.thuc;

	return kq;
}
SoPhuc SoPhuc::operator/(const SoPhuc &other)const
{
	SoPhuc kq;
	int d = other.thuc * other.thuc + other.ao * other.ao;
	kq.thuc = (float)(thuc * other.thuc + ao * other.ao) / d;;
	kq.ao = (float)(other.thuc * ao - thuc * other.ao) / d;
	return kq;
}
bool SoPhuc::operator==(const SoPhuc& other)
{
	return this->thuc == other.thuc && this->ao == other.ao;
}
bool SoPhuc::operator!=(const SoPhuc& other)
{
	return this->thuc != other.thuc || this->ao != other.ao;
}
