#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<map>
#include<algorithm>
using namespace std;

static bool cmp(pair<int,int>a,pair<int,int>b)
{
    return a.second>b.second;
}
vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int,int>mp;
        int n=nums.size();
        for(int i=0;i<n;++i)
            mp[nums[i]]++;
        vector<pair<int,int>>match;
        for(auto m:mp)
            match.push_back({m.first,m.second});
        sort(match.begin(),match.end(),cmp);
        vector<int>ans;

        int cur=0;
        while(1)
        {
            ans.push_back(match[cur++].first);
            if(cur==k) break;
        }
        return ans;
}
int main()
{
    vector<int>arr={1,1,1,2,2,3};
    topKFrequent(arr,2);
    //Output: [1,2]
    
  
}