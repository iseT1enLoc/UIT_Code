#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<sstream>
using namespace std;
/*
nums=[1,2,3]
target=4;
dp size=5;
where dp[i] is the total way to form number i;
How many way to form 0: 1 way;

how many ways to form 1: 1 way;
how many ways to form 2: nums[1]=2 by itself, and we can take 1+1=2 thus we have 2 ways;
how many ways to form 3: nums[2]=3 by itself and we can combine 1&2 in order to add up to 3=>4 way;
how many ways to form 4: dp[4]=dp[3]+dp[2]+dp[1];

*/
int combinationSum4(vector<int>& nums, int target) {
        int len=nums.size();
        vector<unsigned long long>dp(target+1,0);
        dp[0]=1;
        for(int i=1;i<=target;++i)
            for(int j=0;j<len;++j)
                if(i-nums[j]>=0)
                    dp[i]=dp[i]+dp[i-nums[j]]; 

        return (int)dp[target];
}
int main()
{
    vector<int>nums={1,2,3};
    cout<<combinationSum4(nums,4);
}