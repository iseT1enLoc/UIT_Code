#include<iostream>
#include<vector>
using namespace std;

//Minimum Falling PathSum
/*
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. 
Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).*/
int minFallingPathSum(vector<vector<int>>& matrix) 
{
        int row=matrix.size();
        int col=matrix[0].size();

        int dp[row][col];
        for(int i=0;i<col;++i)
            dp[row-1][i]=matrix[row-1][i];
        
        for(int i=row-2;i>=0;--i)
        {
            for(int j=col-1;j>=0;--j)
            {
                if(j==(col-1))
                {
                    dp[i][j]=matrix[i][j]+min( dp[i+1][j] ,dp[i+1][j-1]);
                }
                else if(j==0)
                {
                    dp[i][j]=matrix[i][j]+min(dp[i+1][j],dp[i+1][j+1]);
                }
                if(j!=0&&j!=(col-1))
                {
                    dp[i][j]=matrix[i][j]+min(dp[i+1][j-1],min(dp[i+1][j],dp[i+1][j+1]));
                }
            }
        }
        int minval=10000;
        for(int i=0;i<col;++i)
            if(dp[0][i]<minval) minval=dp[0][i];
        return minval; 
}
int main()
{
    vector<vector<int>>grid=
    {
        {2,1,3},
        {6,5,4},
        {7,8,9},
    };
   cout<<minFallingPathSum(grid);
}