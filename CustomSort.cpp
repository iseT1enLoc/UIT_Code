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
bool Ascending(int a, int b)
{
	return a < b;
}
bool Descending(int a, int b)
{
	return a > b;
}
void CustomSort(int* a, int n, bool (*compareFunc)(int, int))
{
	for (int i = 0; i < n; i++)
	{
		int min_pos= i;
		for (int j = i + 1; j < n; j++)
		{
			if (compareFunc(a[j], a[min_pos]))  min_pos=j;
		}
		swap(a[i], a[min_pos]);
	}
}
int main()
{
	int n, x;
	int* a = new int[100];
	bool (*increasing)(int, int) = Ascending;
	bool (*decreasing)(int, int) = Descending;
	cout << "\nOption1: Enter array and printf in ascending order";
	cout << "\nOption2: Enter array and printf in descending order";
	cout << "\nEnter your option: ";
	cin >> x;
	while (x == 1 || x == 2)
	{
		switch (x)
		{
			case 1:
				cout << "\nEnter the number of element: "; cin >> n;
				input(a,n);
				cout << "\nThe array you'just entered : ";
				output(a,n);
				CustomSort(a, n, increasing);
				cout << "\nAfter sorting, we have the ascending array: ";
				output(a, n);
				break;
			default:
				cout << "\nEnter the number of element: "; cin >> n;
				input(a, n);
				cout << "\nThe array you'just entered : ";
				output(a, n);
				CustomSort(a, n, decreasing);
				cout << "\nAfter sorting, we have the descending array: "; 
				output(a, n);
				break;
		}
		cout << "\nEnter your option: "; cin >> x;
	}

}