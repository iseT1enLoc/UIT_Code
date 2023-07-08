#include<iostream>

/*
problem: climbing stair (k steps)
    we are climbing a stair case. It takes n steps to reach the top.
    Each time we either choose to claim 1....k steps;
    in how many distinct way can we reach the top?

FrameWork for solving DP:
    1.Define the objective function;
        f(i) is the number of distinct ways to reach the ith stair by making 1 to k steps;
    2.Identify base case;
        f(0)=1;
        f(1)=1;
    3.Write down the recurrence relation for the obtimize objective function
        f(n)=f(n-1)+f(n-2)+f(n-3)+.....f(n-k);
    4.what's the order of execution?
        bottom-up;
    5.Where to look for the answer;

This explaination is of channel youtube named "Andrey Grehov"
link: https://www.youtube.com/@andreygrehov
*/
using namespace std;
int climbingStair(int n,int k)
{
    int dp[n+1]={0};
    dp[0]=1;
    dp[1]=1;

    for(int i=2;i<=n;++i)
    {
        for(int j=1;j<=k;++j)
        {
            if(i<j) continue;
            dp[i]=dp[i]+dp[i-j];
        }
    }
    return dp[n];
}
int main()
{
    cout<<"answer: "<<climbingStair(3,3);
    return 0;
}