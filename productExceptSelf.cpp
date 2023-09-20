#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<sstream>

using namespace std;
/*
238.product of array except self;

[1,2,3,4] product except self so that we try to calculate in advance the product of left side and right side of 
each number then interate through the array index and multiply two respective results to have the final answer;
*/
vector<int> productExceptSelf(vector<int>& nums) {
    int n=nums.size();
    
    vector<int>rProduct(n);
    rProduct[0]=1;
    for(int i=1;i<n;++i)
        rProduct[i]=nums[i-1]*rProduct[i-1];

    vector<int>lProduct(n);
    lProduct[n-1]=1;
    for(int i=n-2;i>=0;--i)
        lProduct[i]=nums[i+1]*lProduct[i+1];

    vector<int>ans(n);
    for(int i=0;i<n;++i)
        ans[i]=lProduct[i]*rProduct[i];
    return ans;
}
int main()
{
    vector<int>arr={1,2,3,4};
    productExceptSelf(arr);
    //[24,12,8,6]
}