#include <bits/stdc++.h>
using namespace std;

int longestArithSeqLength(vector<int>&nums)
{
        int n=nums.size();
        vector<unordered_map<int,int>>dp(n);
        int maxlen=0;
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<i;++j)
            {
                int diff=nums[i]-nums[j];
                if(dp[j].count(diff))
                    dp[i][diff]=dp[j][diff]+1;
                else dp[i][diff]=2;
                maxlen=max(maxlen,dp[i][diff]);
            }
        }
        return maxlen;
}
int main()
{
    vector<int>arr={20,1,15,3,10,5,8};
    cout<<longestArithSeqLength(arr);
    //20,15,10,5
    
}