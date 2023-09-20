#include <bits/stdc++.h>
#include<vector>
using namespace std;

/*
6921. Split Strings by Separator
Given an array of strings words and a character separator, split each string in words by separator.

Return an array of strings containing the new strings formed after the splits, excluding empty strings.
Notes

separator is used to determine where the split should occur, but it is not included as part of the resulting strings.
A split may result in more than two strings.
The resulting strings must maintain the same order as they were initially given.
*/
 vector<string> splitWordsBySeparator(vector<string>& words, char separator) {
   int len=words.size();
   vector<string>ans;
   for(int i=0;i<len;++i)
   {
        for(int j=0;j<words[i].size();++j)
        {
            if(words[i][j]==separator) words[i][j]=' ';
        }
        stringstream ss(words[i]);
        string temp;
        while (ss>>temp)
        {
            ans.push_back(temp);
        }  
   }
    return ans;
}
int main()
{
    vector<string> words={ "one.two.three", "four.five", "six" };

    vector<string>ans=splitWordsBySeparator(words,'.');
    for(auto m:ans) cout<<m<<' ';

    cout<<'\n';
    vector<string>words2={"$easy$","$problem$"};
    vector<string>ans2=splitWordsBySeparator(words2,'$');
    for(auto n:ans2) cout<<n<<' ';
}