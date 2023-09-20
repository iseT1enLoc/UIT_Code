#include <bits/stdc++.h>
#include<vector>
using namespace std;

/*
3. Longest Substring Without Repeating Characters

Approach:
Using a set to help recognize the duplicate character in the current string;
We are allowed to append set when the s[i+k] (i+1<=k<=length(s)-1) doesn't appear in the set;otherwise break the appending process;
The current max value is the maximum of cmax and the size of set or position jth - position ith.
Return the current maximum length.
Given a string s, find the length of the longest 
substring without repeating characters.

EXAMPLE:

input: s = "abcabcbb";
Output: 3
Explanation: The answer is "abc", with the length of 3.

*/
int lengthOfLongestSubstring(string s) {
       int len=s.size();
       if(len<=1) return len;
       int cmax=1;
       int i,j;
       for(i=0;i<len-1;++i)
       {
           set<char>se;
           se.insert({s[i]});
           for(j=i+1;j<len;++j)
           {
               if(se.count(s[j])==1)
                    break;
               else 
                    se.insert({s[j]});
           }  
           cmax=max(cmax,j-i);
       }
       return cmax;
    }
int main()
{
    cout<<lengthOfLongestSubstring("abcabcbb");
    
}