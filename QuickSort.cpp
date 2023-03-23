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
int Partition(int* a, int left, int right)
{
	int pos = left - 1;
	for (int i = left; i <= right - 1; i++)
	{
		if (a[i] < a[right])
		{
			pos++;
			swap(a[pos],a[i]);
		}
	}
	pos++;
	swap(a[right],a[pos]);
	return pos;
}
void QuickSort(int* a, int left,int right)
{
	if (left < right)
	{
		int iPivot = Partition(a, left, right);
		QuickSort(a, left, iPivot - 1);
		QuickSort(a, iPivot + 1, right);
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
	QuickSort(a, 0, n - 1);
	cout << "After sorting we have the ascending array:  "; output(a, n);
}