#include<iostream>
using namespace std;

13 6 7 3 8 9 2

3 6 7 13 8 9 2


int check[10] ={};
int arr[10]={1,4,5,23,56,3,87,23,9,13};

int main(){
    int cur_odd,cur_even;

    for(int i=0;i<10;++i){
        if(arr[i]%2==0)
        {
            cur_even=i;
            break;
        }
    }
    for(int i=0;i<10;++i)
    {
        if(arr[i]%2!=0)
        {
            cur_odd = i;
            break;
        }
    }
}