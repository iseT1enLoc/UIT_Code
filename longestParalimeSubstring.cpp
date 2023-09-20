#include<iostream>
#include<string>
using namespace std;


/*
Given a string s, return the longest 
palindromic
substring
 in s.

 example:  "abab"->>ans="aba"||ans="bab"
 example: "cbbc"->>ans="bb";

 the ans has two cases where the size can be either odd or even number;
 to handle this we can double check by pointers (high,low) (r,l) according with the two cases.
 after each checking step we check wheter the new paralime substring is longer the so far answer.
    if true =>>assign a new ans by new substring we've obtained;
    else continue;
 */
string longestPalindrome(string s) {
        int len=s.size();
        string ans="";
        int reslen=0;
        for(int i=0;i<len;++i)
        {
            int low=i;
            int high=i;
            while(low>=0&&high<len&&s[low]==s[high])
            {
                if((high-low+1)>reslen) 
                {
                    reslen=high-low+1;
                    ans=s.substr(low,reslen);
                }
                --low,++high;
            }
            int l=i;
            int r=i+1;
            while(l>=0&&r<len&&s[l]==s[r])
            {
                if((r-l+1)>reslen)
                {
                    reslen=r-l+1;
                    ans=s.substr(l,reslen);
                } 
                --l,++r;
            }
        }
        return ans;
}
int main()
{
    string s="babad";
    cout<<longestPalindrome(s);
 
}