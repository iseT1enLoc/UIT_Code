#include<iostream>
#include<vector>
using namespace std;

/*
Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself.
For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

INPUT: n=12;
Output: 3;
explanation: 4+4+4

Explanation for the solution below:
    array dp with size n+1 so it is easy to operate with as dp[i] 
    is the least number of perfect square numbers that sum to dp[i];
  */
int numSquares(int n) {
        vector<int>dp(n+1,n+1);
        dp[0]=0;
        if(n<4) return n;
        for(int target=1;target<=n;++target)
        {
            for(int s=1;s<target;++s)
            {
                int square=s*s;
                if(target-square<0) break;
                dp[target] = min(1 + dp[target - square],dp[target]);
            }
        }
        return dp[n];
}

int main()
{
    cout<<numSquares(12);
}