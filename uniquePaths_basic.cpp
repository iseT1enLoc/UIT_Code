#include<iostream>
using namespace std;

/*
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]).
The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). 
The robot can only move either down or right at any point in time.
Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to 2 * 109.
*/
/*
using dynamic programing;
    Framework:
    step1: form the objective function
        f(i,j) is the total number of way to get to the grid[x][y];
    step 2: base case
    matrix size 1x1 has 1 way
    matrix size 2*2 has 2 ways
    step 3:
    f(i,j)=f(i-1,j)+f(i,j-1);
*/
/*
    ----------------
    | 1 | 1 | 1 | 1 |
    -----------------
    | 1 | 2 | 3 | 4 | 
    -----------------
    | 1 | 3 | 6 | E | 
    -----------------
    
    Run code step by step
    i=0
      j=0  dp[0][0]=1;
      j=1  dp[0][1]=1;
      j=2  dp[0][2]=1;
      j=3  dp[0][3]=1;
    i=1
      j=0  dp[1][0]=1;
      j=1  dp[1][1]=dp[1][0]+dp[0][1]=2;
      j=2  dp[1][2]=dp[1][1]+dp[0][2]=2+1=3
      j=3  dp[1][3]=dp[1][2]+dp[0][3]=3+1=4
    i=2
      j=0  dp[2][0]=dp[1][0]=1;
      j=1  dp[2][1]=dp[2][0]+dp[1][1]=1+2=3;
      j=2  dp[2][2]=dp[1][2]+dp[2][1]= 3+3=6;
      j=3  dp[2][3]=dp[2][2]+dp[1][3]=6+4;


*/
int uniquePath(int m,int n)
{
    int dp[m][n];
    dp[0][0]=1;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(i>0&&j>0)
            {
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
            else if(i>0)
            {
                dp[i][j]=dp[i-1][j];
            }
            else if(j>0)
            {
                dp[i][j]=dp[i][j-1];
            }
        }
    }
    return dp[m-1][n-1];

}

