#include<iostream>
#include<vector>
using namespace std;

/*   j=cols,i=rows           Here is the dp table, each square represent for the current longest length
------------------------        explain for A:
|   | a | b | c | d | e |               because text1[i]==text2[j] so we add to the current length 1 unit
------------------------                    dp[1][1]=dp[0][0]+1=2
| a | 1 | 1 | 1 | 1 | 1 |               text1[i]==text2[j]=>dp[m-1][n-1]=dp[1][1]+1;
-------------------------
| c | 1 | 1 | A | 2 | 2 |   
-------------------------
| e | 2 | 2 | 2 | 2 | b |   
-------------------------


*/

int longestCommonSubsequence(string text1, string text2) {
        int ans=0;
        int m=text1.size();//row
        int n=text2.size();//col
        vector<vector<int>>dp(m,vector<int>(n));
        if(text1[0]==text2[0]) dp[0][0]=1;
        else dp[0][0]=0;
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(i>0&&j>0)
                {
                    if(text1[i]==text2[j]) dp[i][j]=dp[i-1][j-1]+1;
                    else dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
                }
                else if(i==0&&j>0)
                {
                    if(text1[i]==text2[j]) dp[i][j]=1;
                    else dp[i][j]=dp[i][j-1];
                }
                else if(j==0&&i>0)
                {
                    if(text1[i]==text2[j]) dp[i][j]=1;
                    else dp[i][j]=dp[i-1][j];
                }
            }
        }
        ans=dp[m-1][n-1];
        return ans;
}
int main()
{
    cout<<longestCommonSubsequence("ace","abcde");
}