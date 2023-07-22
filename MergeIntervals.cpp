#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
my answer
vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int ia=0;
        vector<vector<int>>ans;
        ans.push_back(vector<int>());
        int m=intervals.size();
        sort(intervals.begin(),intervals.end());
        ans[0].push_back(intervals[0][0]);
        ans[0].push_back(intervals[0][1]);
        for(int i=1;i<m;++i)
        {
            if(intervals[i][0]<=ans[ia][1])
            {
                ans[ia][1]=max(intervals[i][1],ans[ia][1]);
            }
            else
            {
                ans.push_back(vector<int>());
                ++ia;
                ans[ia].push_back(intervals[i][0]);
                ans[ia].push_back(intervals[i][1]);
            }
        }
        return ans;
}*/
//INTERESTING SOLUTION

vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
        for(int i=1;i<intervals.size();)
        {
            if(intervals[i-1][1]>=intervals[i][0])
            {
                intervals[i-1][1]=max(intervals[i-1][1],intervals[i][1]);
                intervals.erase(intervals.begin()+i);
            }
            else ++i;
        }
        return intervals;
}
int main()
{
    vector<vector<int>>arr={{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>>ans=merge(arr);
    for(auto m:ans)
    {
        for(auto n:m)
        {
            cout<<n<<' ';
        }
        cout<<'\n';
    }
    
}

