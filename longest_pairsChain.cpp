#include <bits/stdc++.h>
#include<vector>
using namespace std;

/*
646. Maximum Length of Pair Chain
We use vector dp to store the maximum of longest length where dp[i] (0<=i<=length(pairs)-1) is the maximum length of chain up to ith
position.
To make it easier for the calculating process we sort the pairs matrix before doing some following operations, let look the second example
pairs = [[1,2],[7,8],[4,5]]
=>after sorting we have:
pairs=[[1,2],[4,5],[7,8]]
Initially, each row has the longest length which is one by itself, then
iterate through the matrix rows, if it meets the constraints, we have the new length at the ith position;
*/
int findLongestChain(vector<vector<int>>& pairs) {
        int m=pairs.size();
        vector<int>dp(m,1);
        sort(pairs.begin(),pairs.end());
        for(int i=1;i<m;++i)
            for(int j=0;j<i;++j)
                if(pairs[j][1]<pairs[i][0])
                    dp[i]=max(dp[i],dp[j]+1);
        return *max_element(dp.begin(),dp.end());
}
int main()
{
    vector<vector<int>>pairs={
        {1,2},
        {7,8},
        {4,5}
    };
    cout<<findLongestChain(pairs);
    
}