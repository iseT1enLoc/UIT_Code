#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>>ans;
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int m=intervals.size();

    sort(intervals.begin(),intervals.end());
    ans.push_back(intervals[0]);
    int temp=intervals[0][1];
    for(int i=1;i<m;++i)
    {
        if(temp>=intervals[i][0])
        {
            temp=max(intervals[i][1],temp);
            ans.back()[1]=temp;
        }
        else
        {
            ans.push_back(intervals[i]);
            temp=intervals[i][1];
        }
    }
    return ans;
}

int main()
{
    vector<vector<int>>intervals={
        {1,3},{2,6},{8,10},{15,18}
    };
    merge(intervals);
    for(auto m:ans)
    {
        for(auto n:m)
        {
            cout<<n<<'\t';
        }
        cout<<'\n';
    }
}