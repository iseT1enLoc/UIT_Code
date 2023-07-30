#include<iostream>
#include<vector>
#include<set>
using namespace std;

/*
2799. Count Complete Subarrays in an Array||leetcode weekly contest;
You are given an array nums consisting of positive integers.
We call a subarray of an array complete if the following condition is satisfied:
The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
Return the number of complete subarrays.

A subarray is a contiguous non-empty part of an array.
*/
int countCompleteSubarrays(vector<int>& nums) {
    set<int>se;
    for(int i=0;i<nums.size();++i)
        se.insert({nums[i]});
 
    int distinct=se.size();
    
    int ans=0;
    for(int left=0;left<nums.size();++left)
    {
        set<int>filter;
        int right=left;
        while(right<nums.size()&&right-left+1<=distinct)//when the size of current sub array is less than the 
        {                                               //number of distinct elements
            filter.insert({nums[right]});
            ++right;
        }
        //substract by one because the previous loop let the right bigger than 1 unit compare to the current position
        --right;
        while(right<nums.size())
        {
            filter.insert({nums[right]});
            if(filter.size()==distinct)++ans;
            ++right;
        }
    }
    return ans;
}
int main()
{
    vector<int>arr={1,3,1,2,2};
    cout<<countCompleteSubarrays(arr);
    //[1,3,1,2],[1,3,1,2,2],[3,1,2],[3,1,2,2];
}