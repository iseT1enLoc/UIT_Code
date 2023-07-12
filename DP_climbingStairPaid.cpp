#include<iostream>
#include<vector>

using namespace std;
/*
problems:
    paid stair case;
    You are climbing a paid stair case. it takes n step to reach to the top andd you have to pay p[i] when step on the ith stair.
    Each time you can climb 1 or 2 steps.
    Return the cheapest path to the top of the staircase
*/
int climbingPaid(int n,vector<int>&paid)
{
    vector<int>dp(n+1,0);
    dp[0]=0;
    dp[1]=paid[1];
    for(int i=2;i<=n;++i)
    {
        dp[i]=paid[i]+min(dp[i-1],dp[i-2]);
    }
    return dp[n];
}
int main()
{
    vector<int>cost={0,3,2,4};
    cout<<"answer: "<<climbingPaid(3,cost);
}