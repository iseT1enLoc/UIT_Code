#include<iostream>
using namespace std;
int n, a[100], k;
void printf_string()
{
	for (int i = 1; i <= k; i++)
		cout << a[i];
	cout << endl;
}
void Combi(int i)
{
	for (int j = a[i - 1] + 1; j <= n - k + i; j++)
	{
		a[i] = j;
		if (i == k)
		{
			printf_string();
		}
		else
		{
			Combi(i + 1);
		}
	}
}

int main()
{
	cin >> n >> k;
	memset(a, 0, sizeof(a));
	Combi(1);
}