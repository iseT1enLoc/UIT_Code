#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int longestConsecutive(vector<int>& nums) {
        int cmax=0;
        set<int>se;
        for(int i=0;i<nums.size();++i)
            se.insert({nums[i]});
        int slen=se.size();
        vector<int>dp(slen,1);
        for(auto num:se)
        {
            if(se.count(num-1)==1) continue;//if num has the element that is equal to num-1 meaning if not the beginning
            else                            //the increasing longest consecutive sequence
            {
                int number=num;
                int count=1;
                while(se.count(number+count))
                {
                    ++count;
                }
                cmax=max(cmax,count);
            }
        }
        return cmax;
}
int main()
{
   vector<int>arr={9,1,4,7,3,-1,0,5,8,-1,6};
   cout<<longestConsecutive(arr);

}

