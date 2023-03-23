#include <iostream>
#include<cmath>
#include<iomanip>
#include<map>
#include<vector>
#include <algorithm>
#include<set>
using namespace std;
struct DonThuc {
    float heso;
    int  somu;
};
struct DaThuc {
    DonThuc  A[50];
};

void NhapDaThuc(DaThuc& p, int& n);
void XuatDaThuc_MuGiamDan(DaThuc& p, int m);
void XuatGiuNguyen(DaThuc a, int n);
void CongDaThuc(DaThuc a, int n, DaThuc p, int m, DaThuc& add, int& k);
void TruDaThuc(DaThuc a, int n, DaThuc p, int m, DaThuc& sub, int& s);
void NhanDaThuc(DaThuc a, int n, DaThuc p, int m, DaThuc& multi, int& e);
double GiaTriDaThucTaiX(DaThuc a, int n, float X);
int BacCaoNhat(DaThuc a, int n);
int main() {
    DaThuc a, b;
    float x;
    int a1, k;
    DaThuc c, d;
    int c1, d1, b1;

    DaThuc add, sub, multi;
    int add1, sub1, multi1;
    cout << "Cac lua chon: ";
    cout << "\nChon 1: nhap xuat mot da thuc.";
    cout << "\nChon 2: nhap vao da thuc va tinh toan gia tri da thuc vua nhap tai gia tri x.";
    cout << "\nChon 3: nhap vao mot da thuc bat ki, xuat theo so mu giam dan va bac cao nhat cua da thuc.";
    cout << "\nChon 4: nhap vao hai da thuc, thuc hien phep cong, tru, nhan hai da thuc do. ";
    cout << "\nNhap nhung so khac: ket thuc chuong trinh.";
    cout << "\nNhap lua chon: "; cin >> k;
    while (k != 0)
    {
        
        switch (k)
        {
            case 1:
                NhapDaThuc(a, a1);
                cout << "\nDa thuc vua nhap la: ";
                XuatGiuNguyen(a, a1 - 1);
                break;
            case 2:
                NhapDaThuc(b, b1);
                cout << "\nDa thuc vua nhap la: "; XuatGiuNguyen(b, b1 - 1);
                cout << "\nNhap gia tri x: ";
                cin >> x;
                cout << "\nGia tri cua da thuc tai x= " << x << " la: " << GiaTriDaThucTaiX(b, b1, x);
                break;
            case 3:
                cout << "\nNhap da thuc: ";
                NhapDaThuc(a, a1);
                cout << "\nDa thuc vua nhap la: ";
                XuatGiuNguyen(a, a1 - 1);
                cout << "\nXuat da thuc theo so mu giam dan: ";
                XuatDaThuc_MuGiamDan(a, a1 - 1);
                cout << "\nBac cao nhat cua da thuc: " << BacCaoNhat(a, a1);
                break;
            case 4:
                cout << "\nNhap da thuc thu nhat.";
                NhapDaThuc(c, c1);
                cout << "\nDa thuc vua nhap la: ";
                XuatDaThuc_MuGiamDan(c, c1 - 1);
                cout << "\nNhap da thuc thu hai.";
                NhapDaThuc(d, d1);
                cout << "\nDa thuc vua nhap la: ";
                XuatDaThuc_MuGiamDan(d, d1 - 1);
                cout << endl;
                cout << "\nKet qua phep cong hai da thuc: ";
                CongDaThuc(c, c1, d, d1, add, add1);
                XuatDaThuc_MuGiamDan(add, add1-1);
                cout << "\nKet qua phep tru hai da thuc: ";
                TruDaThuc(c, c1, d, d1, sub, sub1);
                XuatDaThuc_MuGiamDan(sub,sub1-1);
                cout << "\nKet qua phep nhan hai da thuc: ";
                NhanDaThuc(c, c1, d, d1, multi, multi1);
                XuatDaThuc_MuGiamDan(multi, multi1 - 1);
                break;
        }
        cout << "\n\nNhap lua chon: "; cin >> k;
    }
}
void NhapDaThuc(DaThuc& p, int& n) {
    cout << "\nSo luong don thuc: ";
    cin >> n;
    cout << "Nhap vao lan luot he so - so mu: " << endl;
    for (int i = n - 1; i > 0; i--) {
        cin >> p.A[i].heso >> p.A[i].somu;
    }
    cout << "Nhap don thuc cuoi: "; cin >> p.A[0].heso >> p.A[0].somu;
   
}
void XuatDaThuc_MuGiamDan(DaThuc& p, int m) {
    map<int, double, greater<int>>mp;
    float s = 0;
    for (int i = m; i >= 0; i--) {
        mp.insert(pair<int, double>(p.A[i].somu, p.A[i].heso));
    }
    bool OK = 0;
    for (auto it : mp) {
        s += it.second;
        if (it.second == 0) continue;
        else {
            if (OK) {
                if (it.second > 0) cout << "+";
            }
            if (!(it.first == 1 || it.first == 0)) {
                if (it.second == 1) cout << "x^" << it.first;
                else if (it.second == -1) cout << "-x^" << it.first;
                else cout << it.second << "x^" << it.first;
                OK = 1;
            }
            if (it.first == 1) {
                if (it.second == 1) cout << "x";
                else if (it.second == -1) cout << "-x";
                else cout << it.second << "x";
                OK = 1;
            }
            if (it.first == 0)
            {
                if (it.second == 1) cout << 1;
                else if (it.second == -1) cout << -1;
                else cout << it.second;
                OK = 1;
            }

        }

    }
    if (s == 0) cout << 0;
}
void XuatGiuNguyen(DaThuc a, int n) {
    bool OK = 0;
    double s = 0;
    for (int i = n; i >= 0; i--) {
        s += a.A[i].heso;
        if (a.A[i].heso == 0) continue;
        else {
            if (OK) {
                if (a.A[i].heso > 0) cout << "+";
            }
            if (!(a.A[i].somu == 1 || a.A[i].somu == 0)) {
                if (a.A[i].heso == 1) cout << "x^" << a.A[i].somu;
                else if (a.A[i].heso == -1) cout << "-x^" << a.A[i].somu;
                else cout << a.A[i].heso << "x^" << a.A[i].somu;
                OK = 1;
            }
            if (a.A[i].somu == 1) {
                if (a.A[i].heso == 1) cout << "x";
                else if (a.A[i].heso == -1) cout << "-x";
                else cout << a.A[i].heso << "x";
                OK = 1;
            }
            if (a.A[i].somu == 0)
            {
                if (a.A[i].heso == 1) cout << 1;
                else if (a.A[i].heso == -1) cout << -1;
                else cout << a.A[i].heso;
                OK = 1;
            }

        }
    }
    if (s == 0) cout << 0;
}
void CongDaThuc(DaThuc a, int n, DaThuc p, int m, DaThuc& add, int& k) {
    multimap<int, float>mp;
    set<int>se;
    for (int i = 0; i < n; i++) {
        mp.insert({ a.A[i].somu,a.A[i].heso });
        se.insert({ a.A[i].somu });
    }
    for (int i = 0; i < m; i++) {
        mp.insert({ p.A[i].somu,p.A[i].heso });
        se.insert({ p.A[i].somu });
    }
    k = se.size();
    auto dem = se.begin();
    int kq = 0;
    int mu = 0;
    for (auto m : se)
    {
        add.A[mu].somu = m;
        add.A[mu].heso = 0;
        mu++;
    }
    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        if ((*it).first == (*dem))
        {
            add.A[kq].heso = add.A[kq].heso + (*it).second;
        }
        else
        {
            kq++;
            dem++;
            add.A[kq].heso = add.A[kq].heso + (*it).second;
        }

    }
    mp.clear();
    se.clear();

}
void TruDaThuc(DaThuc a, int n, DaThuc p, int m, DaThuc& sub, int& s) {
    for (int i = 0; i < m; i++)
    {
        p.A[i].heso = -1.0 * p.A[i].heso;
    }
    CongDaThuc(a, n, p, m, sub, s);
}
void NhanDaThuc(DaThuc a, int n, DaThuc p, int m, DaThuc& multi, int& e)
{
    multimap <int, float>mp;
    set<int>se;
    DaThuc* mul = new DaThuc[max(m, n)];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mul[i].A[j].somu = a.A[i].somu + p.A[j].somu;
            mul[i].A[j].heso = a.A[i].heso * p.A[j].heso;
            se.insert({ mul[i].A[j].somu });
            mp.insert({ mul[i].A[j].somu,mul[i].A[j].heso });
        }
    }
    e = (int)se.size();
    int kq = 0; int mu = 0;
    for (auto m : se)
    {
        multi.A[mu].somu = m;
        multi.A[mu].heso = 0;
        mu++;
    }
    auto dem = se.begin();
    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        if ((*it).first == (*dem))
        {
            multi.A[kq].heso = (*it).second + multi.A[kq].heso;
        }
        else
        {
            ++kq; ++dem;
            multi.A[kq].somu = *dem;
            multi.A[kq].heso = (*it).second + multi.A[kq].heso;
        }
    }
}
double GiaTriDaThucTaiX(DaThuc a, int n, float X) {
    double sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum += a.A[i].heso * pow(X, a.A[i].somu);
    }
    return sum;
}
int BacCaoNhat(DaThuc a, int n)
{
    set<int, greater<>>se;
    for (int i = 0; i < n; i++)
    {
        se.insert({ a.A[i].somu });
    }
    auto kq = se.begin();
    return *kq;
}