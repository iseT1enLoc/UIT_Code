#include"PhanSo.h"
using namespace std;
PhanSo::PhanSo()
{
	tuso = new int;
	*tuso = 0;
	mauso = new int;
	*mauso = 1;
}
/*
PhanSo::~PhanSo()
{
	delete tuso;
	tuso = NULL;
	delete mauso;
	mauso = NULL;
}*/
PhanSo::PhanSo(const PhanSo&ps)
{
	this->tuso = ps.tuso;
	this->mauso = ps.mauso;
}
PhanSo& PhanSo::operator=(const PhanSo&ps)
{
	if (*tuso == *ps.tuso && *mauso == *ps.mauso) 
		return *this;//kiem tra tranh truong hop gan bang chinh no

	this->tuso = ps.tuso;
	this->mauso = ps.mauso;
	return*this;
}
PhanSo::PhanSo(int tuso, int mauso)
{
	this->tuso = new int;
	*this->tuso = tuso;

	this->mauso = new int;
	*this->mauso = mauso;
}
PhanSo PhanSo::operator+(const PhanSo&ps)
{
	PhanSo KetQua;
	*KetQua.tuso = (*tuso) * (*ps.mauso) + (*mauso) * (*ps.tuso);
	*KetQua.mauso = (*mauso) * (*ps.mauso);
	return KetQua;
}
PhanSo PhanSo::operator-(const PhanSo&ps)
{
	PhanSo KetQua;
	*KetQua.tuso = (*tuso) * (*ps.mauso) - (*mauso) * (*ps.tuso);
	*KetQua.mauso = (*mauso) * (*ps.mauso);
	return KetQua;
}
PhanSo PhanSo::operator*(const PhanSo&ps)
{
	PhanSo KetQua;
	*KetQua.tuso = *tuso * (*ps.tuso);
	*KetQua.mauso = *mauso * (*ps.mauso);
	return KetQua;
}
PhanSo PhanSo::operator/(const PhanSo&ps)
{
	PhanSo KetQua;
	*KetQua.tuso = *tuso * (*ps.mauso);
	*KetQua.mauso = *mauso * (*ps.tuso);
	return KetQua;
}
PhanSo& PhanSo::operator+=(const PhanSo&ps)
{
	*this->tuso= (*this->tuso) * (*ps.mauso) + (*this->mauso) * (*ps.tuso);
	*this->mauso = (*this->mauso) * (*ps.mauso);
	return *this;
}
PhanSo& PhanSo::operator-=(const PhanSo&ps)
{
	*this->tuso = (*this->tuso) * (*ps.mauso) - (*this->mauso) * (*ps.tuso);
	*this->mauso = (*this->mauso) * (*ps.mauso);
	return *this;
}
PhanSo& PhanSo::operator*=(const PhanSo&ps)
{
	*this->tuso = (*this->tuso) * (*ps.tuso);
	*this->mauso = (*this->mauso) * (*ps.mauso);
	return *this;
}

PhanSo& PhanSo::operator/=(const PhanSo&ps)
{
	*this->tuso = (*this->tuso) * (*ps.mauso);
	*this->mauso = (*this->mauso) * (*ps.tuso);
	return *this;
}
bool PhanSo::operator==(const PhanSo&ps)
{
	int Hieu = *this->tuso * (*ps.mauso) - (*this->mauso) * (*ps.tuso);

	if (Hieu == 0)
		return true;
	else
		return false;
}
bool PhanSo::operator<(const PhanSo&ps)
{
	int Hieu = *this->tuso * (*ps.mauso) - (*this->mauso) * (*ps.tuso);
	if (Hieu < 0)
		return true;
	else
		return false;
}
bool PhanSo::operator>(const PhanSo& ps)
{
	int Hieu = *this->tuso * (*ps.mauso) - (*this->mauso) * (*ps.tuso);
	if (Hieu > 0)
		return true;
	else
		return false;
}
bool PhanSo::operator<=(const PhanSo&ps)
{
	return operator<(ps)||operator==(ps);
}
bool PhanSo::operator>=(const PhanSo&ps)
{
	return operator>(ps) || operator==(ps);
}

bool PhanSo::operator!=(const PhanSo&&ps)
{
	return (*tuso) != (*ps.tuso) && (*mauso) != (*ps.mauso);
}
PhanSo PhanSo::operator++(int x)
{
	PhanSo KetQua(*this);

	*this->tuso = *this->tuso + (*this->mauso);

	return KetQua;
}
PhanSo& PhanSo::operator++()
{
	*this->tuso = *this->tuso + (*this->mauso);
	return *this;
}
PhanSo PhanSo::operator--(int x)
{
	PhanSo KetQua(*this);

	*this->tuso = *this->tuso - (*this->mauso);

	return KetQua;
}
PhanSo& PhanSo::operator--()
{
	*this->tuso = *this->tuso - (*this->mauso);
	return *this;
}