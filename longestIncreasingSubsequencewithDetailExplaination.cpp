#include<iostream>
#include<vector>
using namespace std;

//673. Number of Longest Increasing Subsequence
/*
Explaination:
    first we initialize 2 vector dp and cnt, where:
        dp is to store the longest incresing subsequence ending in position ith;
        cnt is used to count the frequency of the subsequence
    Because each single number is the longest increasing sequence itself so we initialize the two vector with number 1;
    vector<int>dp(n,1);
    vector<int>cnt(n,1);
    cmax is variable to keep track of the current longest subsequence value;

    loop from index i=1 to i=n-1(n==nums.size()), at each position we do the following things:
        1.loop from j=0 until j<i
            when nums[j]<nums[i]
                check if the current len dp[i]<dp[j]+1
                    reassign: dp[i]=dp[j]+1;
                              cnt[i]=cnt[j];<=> meaning: if there is more than 1 subsequences with length dp[j]
                                                it results to the same thing to number of subsequence length dp[i]=dp[j]+1;
                else if dp[i]==dp[j]+1:
                        there are other subsequence with the same length;
            after the loop we examine the cmax value one again: cmax=max(cmax,dp[i])
        2.loop through the array dp
        initialize ans=0;
        when the length at position i is equal to cmax, insreasing ans the frequency of that increasing subsequence: ans=ans+cnt[i]
    
    RUNNING CODE STEP BY STEP;
    nums=[1,3,5,4,7]
    dp=[1,1,1,1,1]
    cnt=[1,1,1,1,1]

    i=1;
            .nums[0]<nums[1]&&dp[1]<dp[0]+1
                dp[1]=dp[0]+1=2;//the current longest subsequence ending at position 1th is equal to 2;
                cnt[1]=cnt[0]=1;

                cmax=2;
    i=2
            .nums[0]<nums[2]&&dp[2]<dp[0]+1;
                dp[2]=dp[0]+1=2;
                cnt[2]=cnt[0];
            .nums[1]<nums[2]&&dp[2]<dp[1]+1;
                dp[2]=dp[1]+1=2+1=3;
                cnt[2]=cnt[1]=1;**

                cmax=3;
    i=3
            .nums[0]<nums[3]&&dp[3]<dp[0]+1;
                dp[3]=dp[0]+1=2;
                cnt[3]=cp[0]=1;
            .nums[1]<nums[3]&&dp[3]<dp[1]+1;
                dp[3]=dp[1]+1=3;
                cnt[3]=cnt[1]=1;
            .nums[2]>nums[3] continue;

                cmax=3
            
    i=4
            .nums[0]<nums[4]&&dp[4]<dp[0]+1;
                dp[4]=dp[0]+1=2;
                cnt[4]=cnt[0]=1;
            .nums[1]<nums[4]&&dp[4]<dp[1]+1;
                dp[4]=dp[1]+1=3;
                cnt[4]=cnt[1]=1;
            .nums[2]<nums[4]&&dp[4]<dp[2]+1;
                dp[4]=dp[2]+1=4;
                cnt[4]=cnt[2]=1;
            .nums[3]<nums[4]&&dp[4]==dp[3]+1;
                cnt[4]=cnt[4]+cnt[3];//there is other subsequence is equal to dp[4];

            cmax=4;

                
*/
int findNumberOfLIS(vector<int>& nums) {
   int n=nums.size();
   vector<int>cnt(n,1);
   vector<int>dp(n,1);
   int cmax=1;
   for(int i=1;i<n;++i)
   {
       for(int j=0;j<i;++j)
       {
           if(nums[j]<nums[i]&&dp[j]+1>dp[i])
           {
               dp[i]=1+dp[j];
               cnt[i]=cnt[j];
           }
           else if(nums[j]<nums[i]&&dp[j]+1==dp[i])
                cnt[i]=cnt[i]+cnt[j];
       }
       cmax=max(cmax,dp[i]);
   }  
   int ans=0;
   for(int i=0;i<n;++i)
        if(dp[i]==cmax)
            ans+=cnt[i];
    return ans;
}
int main()
{
   vector<int>nums = {1,3,5,4,7};
   cout<<findNumberOfLIS(nums);
}