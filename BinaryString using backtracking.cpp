#include<iostream>
using namespace std;
int n, a[100], k, used[100];
void printf_string()
{
	for (int i = 1; i <=n; i++)
		cout << a[i];
		cout << endl;
}
void Try(int i)
{
	for (int j = 0; j <= 1; j++)
	{
		a[i] = j;
		if (i == n)
		{
			printf_string();
		}
		else
		{
			Try(i + 1);
		}
	}
}
int main()
{
	cin >> n;
	Try(1);
}