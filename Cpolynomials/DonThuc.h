#pragma once
class DonThuc
{
private:
	int SoMu;
	float HeSo;
public:
	DonThuc();
	void Nhap();
	float LayHeSo();
	int LaySoMu();
	void GanSoMu(int);
	void GanHeSo(float);
};

