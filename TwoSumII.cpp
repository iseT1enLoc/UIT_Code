#include<iostream>
#include<vector>
using namespace std;

/*
Constraints:
2 <= numbers.length <= 3 * 10e4
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.*/

vector<int> twoSum(vector<int>& numbers, int target) {
        int n=numbers.size();
        int low=0;
        int high=n-1;
        vector<int>ans(2);
        while(low<high)
        {
            int sum=numbers[low]+numbers[high];
            if(sum==target) 
            {
                ans[0]=low+1;
                ans[1]=high+1;
                break;
            }
            else if(sum>target) --high;
            else ++low;
        }
        return ans;
}
int main()
{
    vector<int>numbers={2,7,11,15};
    twoSum(numbers,9);
    //OUTPUT: (1,2)

}