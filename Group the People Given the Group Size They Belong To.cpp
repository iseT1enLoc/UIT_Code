#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<map>
#include<algorithm>
using namespace std;
/*
1282. Group the People Given the Group Size They Belong To
*/
static bool cmp(pair<int,int> a,pair<int,int> b)
{   
    return a.second<b.second;
}
vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        int n=groupSizes.size();
        vector<pair<int,int>>match;
        for(int i=0;i<n;++i)
            match.push_back({i,groupSizes[i]});

        sort(match.begin(),match.end(),cmp);
        vector<vector<int>>ans;
        int cur=0;
        while(cur<n)
        {
            vector<int>temp;
            int t=cur;
            int s=match[t].second;
            int cnt=0;
            while(cnt<s)
            {
                temp.push_back(match[t].first);
                ++cnt,++t;
            }
            ans.push_back(temp);
            cur+=cnt;
        }
        return ans;
}
int main()
{
    vector<int>arr={3,3,3,3,3,1,3};
    groupThePeople(arr);
  
}