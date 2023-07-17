#include<iostream>
#include<vector>
using namespace std;

/*
#LONGEST PALINDROMIC SUBSEQUNCE
func 
                                    string s="abccdha"
                                              i     j
                                we see if s[i]==s[j] hence the two character will be included in the final longest palindrome
                                return     2+solve(s,dp,i+1,j-1)=>2+2=4
                                        s="bccdh"=2
                                           i   j
                                    =>s[i]!=s[i] we take maximum of
                                s="bccd" =2                                       s="ccdh"=2
                     s="bcc" =2              s="ccd"=2                  s="ccd" =2               s="cdh"=1
                s="bc"=1      s="cc"     s="cc" s="cd" =1           s="cc"   s="cd" =1     s="cd" =1       s="dh"=1
            s="b"    s="c"     2         2       s="c" s="d"    2      s="c" s="d"  s="c" s="d"   s="d"  s="h"
            1        1                            1      1              1      1    1      1       1      1
                      
*/
int solve(string &s,vector<vector<int>>&dp,int start,int end)
{
         if(start==end) return 1;
         if(start>end) return 0;
         
         if(dp[start][end]!=-1) return dp[start][end];

         if(s[start]==s[end]) return 2+solve(s,dp,start+1,end-1);
         int leaveleft=solve(s,dp,start+1,end);
         int leaveright=solve(s,dp,start,end-1);
         return dp[start][end]=max(leaveleft,leaveright);
}
int longestPalindromeSubseq(string s) {
        int n=s.size();
        vector<vector<int>>dp(n,vector<int>(n,-1));
        int ans=solve(s,dp,0,n-1);
        return ans;
}

int main()
{
cout<<longestPalindromeSubseq("abbsa");
}