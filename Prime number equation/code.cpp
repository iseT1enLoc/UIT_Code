#include<iostream>
using namespace std;

#define MAX 50000
#define MAXN 5000

bool Sieve[MAX + 1] = { 0 };
int aPrime[MAXN], nprime;

void EratosthenesSieve(int n)
{
	int i, j;
	nprime = 0;
	for (i = 2; i < n; i++)
	{
		if (!Sieve[i])
		{
			aPrime[nprime++] = i;
			for (j = i + i; j < n; j += i)
				Sieve[j] = 1;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n,x, y, z, i, j, k;
	cin >> n;
	EratosthenesSieve(n);
	for (i = 0; i < nprime; i++)
	{
		for (j = i; j < nprime; j++)
		{
			z = n - aPrime[i] - aPrime[j];
			if (!Sieve[z])//found
			{
				cout << aPrime[i] << ' ' << aPrime[j] << \
					' ' << z;
				return 0;
			}
		}
	}
	cout << "-1 -1 -1";
	return 0;

}