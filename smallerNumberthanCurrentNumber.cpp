#include<iostream>
#include<algorithm>
#include <utility>
#include<vector>

using namespace std;

/*
Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it.
 That is, for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i].
*/
vector<int> smallerNumbersThanCurrent(vector<int>& nums)
 {
     int n=nums.size();
     vector<pair<int,int>>ans;
    for(int i=0;i<n;++i)
    {
        ans.push_back({nums[i],i});
    }
    sort(ans.begin(),ans.end());
    for(auto m:ans) cout<<m.first;
    vector<int>res(n);
    for(int i=n-1;i>=0;--i)
    {
        int j=0;
        int cur=0;
        while(j<n&&ans[j++].first<ans[i].first) ++cur;
        res[ans[i].second]=cur;
    }
    return res;
 }
int main()
{
    vector<int>arr={1,4,2,0,9};
    smallerNumbersThanCurrent(arr);
}