#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
using namespace std;
//2545.Sort the students by their kth score
/*
-----------------      ------------------------
 10 | 6 | 9 | 1 |      | 7  |  5  |  11  | 2  | 
 7  | 5 | 11| 2 | ==>>>| 10 |  6  |  9   | 1  |
 4  | 8 | 3 | 15|      | 4  |  8  |  3   | 15 |
 ----------------  

*/
vector<vector<int>> sortTheStudents(vector<vector<int>>& score, int k) {
        int m=score.size();//rows
        int n=score[0].size();//cols

        for(int i=0;i<m-1;++i)
        {
            int min_index=i;
            for(int j=i+1;j<m;++j)
            {
                if(score[j][k]>score[min_index][k]) min_index=j;
            }
            for(int j=0;j<n;j++)
            {
                swap(score[i][j],score[min_index][j]);
            }
        }
        return score;
}
int main()
{
    vector<vector<int>>score={
        {10,6,9,1},
        {7,5,11,2},
        {4,8,3,15}
    };
    vector<vector<int>>ans=sortTheStudents(score,2);
    for(auto m:score)
    {
        for(int n:m)
        {
            cout<<n<<'\t';
        }
        cout<<'\n';
    }
}