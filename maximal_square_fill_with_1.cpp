#include<iostream>
#include<vector>
using namespace std;

/*
Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
--------------------------
| 1  | 0  | 1  | 0  | 0  |  
--------------------------                 
| 1  | 0  | 1  | 1  | 1  |
--------------------------
| 1  | 1  | 1  | 1  | 1  |
--------------------------
| 1  | 0  | 0  | 1  | 0  |
--------------------------

*/

int maximalSquare(vector<vector<char>>& matrix) {
        int row=matrix.size();
        int col=matrix[0].size();

        int dp[row+1][col+1];
        for(int i=0;i<=row;++i)
          for(int j=0;j<=col;++j)
            dp[i][j]=0;
        int max_edge=0;
        for(int i=0;i<row;++i)
        {
            for(int j=0;j<col;++j)
            {
                if(matrix[i][j]=='1')
                {
                    dp[i+1][j+1]=min(dp[i][j],min(dp[i+1][j],dp[i][j+1]))+1;
                    if(dp[i+1][j+1]>max_edge) max_edge=dp[i+1][j+1];
                }
            }
        }
        return max_edge*max_edge;
}


int main()
{
 
 
}