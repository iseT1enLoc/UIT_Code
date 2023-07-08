#include<iostream>
#include<vector>
using namespace std;

/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Solution: Dynamic programing approach;
we use an dp array with size amount+1 to store the minimum number of coins of the ith value;
let take an example;
coins={1,2,5};
amount=11;

         0 1 2 3 4 5 6 7 8 9 10 11  
 coins 1 0 1*2 3 4 5 6 7 8 9 10 11
       2 0 1 1*2 2 3 3 4 4 5 5  6 
       5 0 1 1 2 2 1*2 2 3 3 2  3
 
Psuedo code:
    step 1: initialize dp(amount+1,INT_MAX);
    step 2:
        for i=1->i=amount
            for j in coins
        when i>=coins[j] because when the value is less than the coins[j] it has no way to convert
            dp[i]=min of dp[i] and dp[i-coins[j]]+1;
    step 3;
        return dp[amount] if it's not equal to INT_MAX;
        return -1;
*/

int coinChange(vector<int>& coins, int amount) {
       vector<int>dp(amount+1,amount+1);
       dp[0]=0;
       int len=coins.size();
       for(int j=1;j<=amount;++j)
       {
            for(int i=0;i<len;++i)
            {
                if(j>=coins[i])
                {
                    dp[j]=min(dp[j],dp[j-coins[i]]+1);
                }
            }
       }
      if(dp[amount]!=amount+1) return dp[amount];
      return -1;

}
int main()
{
    //example:
    vector<int>arr={1,2,5};
    cout<<coinChange(arr,11);
}