#include<iostream>
using namespace std;
int n, a[100], k, used[100], cnt = 0;
void printf_string()
{
	for (int i = 1; i <= n; i++)
		cout << a[i];
	cout << endl;
}

void permutation(int i)
{
	for (int j = 1; j <= n; j++)
	{
		if (used[j] == 0)
		{
			a[i] = j;
			used[j] = 1;
			if (i == n)
			{
				printf_string();
				cnt++;
			}
			else
			{
				permutation(i + 1);
			}
			used[j] = 0;
		}
	}
}
int main()
{
	cin >> n;
	memset(used, 0, sizeof(used));
	permutation(1);
	cout << "Factorial of " << n << " is equal to " << cnt;
}