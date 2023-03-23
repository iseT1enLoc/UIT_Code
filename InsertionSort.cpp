#include<iostream>
using namespace std;
void input(int* a, int& n)
{
	for (int i = 0; i < n; i++)
		cin >> a[i];
}
void output(int* a, int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << "\t";
	cout << endl;
}
void InsertionSort(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		int j = i;
		while (j > 0 && a[j] < a[j - 1])
		{
			swap(a[j-1],a[j]);
			--j;
		}
	}
}
int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	input(a, n);
	cout << "The array you've just entered: ";
	output(a, n);
	InsertionSort(a, n);
	cout << "After sorting we have the ascending array:  "; output(a, n);
	delete[]a;
	a = NULL;
}