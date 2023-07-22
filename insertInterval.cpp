#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

   vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int len=intervals.size();
        int ok=1;
        for(int i=0;i<len;++i)
        {
            if(intervals[i][1]>=newInterval[0]&&intervals[i][0]<=newInterval[0])
            {
                intervals[i][0]=min(newInterval[0],intervals[i][0]);
                intervals[i][1]=max(newInterval[1],intervals[i][1]);
                ok=0;
                break;
            }  
        }
        //if the newInterval doesn't intersect with any row of the matrix then we insert it to the last position
        if(ok) intervals.insert(intervals.begin()+len,newInterval);
        
        //reform the intervals
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
    vector<vector<int>>matrix={{1,2},{3,5},{6,7},{8,10},{12,16}};
    vector<int>newinterval={4,8};
    insert(matrix,newinterval);
    vector<vector<int>>ans=matrix;
    for(auto m:ans)
    {
        for(auto n:m)
        {
            cout<<n<<' ';
        }
        cout<<'\n';
    }
}

