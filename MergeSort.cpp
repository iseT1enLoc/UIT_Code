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
void Merge(int* a, int left, int mid, int right)
{
	int* half1 = new int[mid - left + 1];
	int* half2 = new int[right - mid];

	int l, r;// create to variable to manage the total number of 1st half and 2nd half;
	l = 0;
	for (int i = left; i <= mid; i++)
		half1[l++] = a[i];
	r = 0;
	for (int j = mid + 1; j <= right; j++)
		half2[r++] = a[j];

	int* temp = new int[l + r];
	int i, j, cnt; //these three variable to manage the temperary position of element in half1,half2,cntrespectively;
	i = 0; j = 0; cnt = 0;
	while (!(i >= l && j >= r))
	{
		if (i < l && j < r && half1[i] < half2[j] || j >= r)
		{
			temp[cnt++] = half1[i++];
		}
		else
		{
			temp[cnt++] = half2[j++];
		}
	}
	
	for (int i = 0; i <cnt; i++)
		a[left + i] = temp[i];

	delete[]temp;
	temp = NULL;
	delete[]half1;
	half1 = NULL;
	delete[]half2;
	half2 = NULL;
}
void MergeSort(int* a, int left, int right)
{
	if (left < right)
	{
		int mid = (right + left) / 2;
		MergeSort(a, left,mid);
		MergeSort(a, mid + 1, right);
		Merge(a, left, mid, right);
	}
}
int main()
{
	int n, x;
	cout << "Enter the number of element: ";
	cin >> n;
	int* a = new int[n];
	input(a, n);
	output(a, n);
	MergeSort(a, 0, n - 1);
	cout << "\nAfter sorting, we have the ascending array: ";
	output(a, n);
	delete[]a;
	a = NULL;
}