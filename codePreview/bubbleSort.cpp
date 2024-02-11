#include<iostream>
using namespace std;

void bubbleSort(int*arr,int n){
    for(int i=0;i<n-1;++i)
    {
        for(int j=0;j<n-1-i;++j)
        {
            if(arr[j]>arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }
}
void InsertionSort(int*arr,int n){
    for(int i=1;i<n;++i)
    {
        int j=i-1;
        int key = arr[i];
        while(key<arr[j]&&j>=0)
        {
            arr[j+1] = arr[j];
             --j;
        }
        arr[j+1]=key;
    }
}
void printArray(int*arr,int n)
{
    for(int i=0;i<n;++i)
    {
        cout<<arr[i]<<' ';
    }
}
void SelectionSort(int*arr,int n){
    for(int i=0;i<n-1;++i)
    {
        int min_val = arr[i];
        int index = i;
        for(int j=i+1;j<n;++j)
            if(arr[j]<min_val)
            {
                min_val = arr[j];
                index = j;
            }
        if(index!=i) swap(arr[index],arr[i]);

    }
}


int main(){
    int arr[10] = {1,3,23,5,34,6,76,2,1,10};
    bubbleSort(arr,10);
    //InsertionSort(arr,10);
    //SelectionSort(arr,10);
    printArray(arr,10);
}