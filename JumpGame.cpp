#include<iostream>
#include<vector>
using namespace std;
/*
You are given an integer array nums. You are initially positioned at the array's first index,
and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.
    [2][3][1][1][4]
    starting from the ending position, simply thinking that if we can find the way to approach the current position from
    its previous one, then reset the target position as the current position
    then loop this process until the  beginning of array

    after the process, the target will be equal to 0 if we can approach the ending position.
*/
bool canJump(vector<int>& nums) {
        int n=nums.size();
        int target=n-1;
        for(int i=n-2;i>=0;--i)
        {
            if(i+nums[i]>=target) target=i;
        }
        return target==0?true:false;
}
int main()
{
    vector<int>arr={2,3,1,1,4};
    cout<<canJump(arr);
}