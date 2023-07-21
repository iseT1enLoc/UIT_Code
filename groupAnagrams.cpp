#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<sstream>

/*
49.GROUP Anagrams
 step1: iterate through the vector of string that contain different words,
        for each position we sort to have the words order in increasing style that make it easier for map
        to realize the same key;
        each key in the map has a vector of different words(group anagrams)
 step2:
    interate through the map, we know that each key contains a group anagrams,
    thus we loop until the end of each key to have the expected answer;
*/
using namespace std;
vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string,vector<string>>mp;   
        int n=strs.size();
        for(int i=0;i<n;++i)
        {
            string s=strs[i];
            sort(strs[i].begin(),strs[i].end());
            mp[strs[i]].push_back(s);
        }

        vector<vector<string>>ans;
        int i=0;
        for(auto m:mp)
        {
            ans.push_back(vector<string>());
            for(int j=0;j<m.second.size();++j)
            {
                ans[i].push_back(m.second[j]);
            }
            ++i;
        }
        return ans;   
}
int main()
{
    vector<string>s={"eat","tea","tan","ate","nat","bat"};
    groupAnagrams(s);
}