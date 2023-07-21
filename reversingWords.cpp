#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<sstream>

using namespace std;

/*
using stringstream to extract each single word then push them into stack;
"a good example"
            First in last out so that we can have the new string with reversing 
' example'  order;
'  good  '
'   a    '
---------- 
*/
string reverseWords(string s) {
        stack<string>st;
        stringstream ss(s);
        string word;
        while(ss>>word)
        {
            st.push(word);
        }
        int t=st.size();
        string ans="";
        while(t>1)
        {
            ans+=(st.top()+' ');
            st.pop();
            --t;
        }
        ans+=st.top();
        return ans;
}
int main()
{
    cout<<reverseWords("a good example");
}