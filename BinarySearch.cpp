#include<iostream>
using namespace std;
int BinarySearch(int* a, int left,int right,int val)
{
	if (left > right) return -1;// return -1 if no match element in the array
	int mid = (right + left) / 2;
	if (a[mid] == val) return mid;
	else if (a[mid] > val) return BinarySearch(a, left, mid - 1,val);
	else return BinarySearch(a, mid + 1, right,val);
}
void input(int* a, int &n)
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
int main()
{
	int n, x;
	cout << "Enter the number of element: ";
	cin >> n;
	int* a = new int[n];
	input(a,n);
	output(a, n);
	cout << "\nEnter x: ";
	cin >> x;
	cout << "The position of the element you are finding is " << BinarySearch(a, 0, n - 1, x);
	delete[]a;
	a = NULL;
}