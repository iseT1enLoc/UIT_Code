#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*508.MOST FREQUENCE SUBTREE*/    
vector<int>tem;
//function to calculate sum of subtree that have root==root
int sumNode(TreeNode*root)
{
    if(!root) return 0;
    return root->val+sumNode(root->left)+sumNode(root->right);
}
//function to pre_compute all the sum subtree
void dfs(TreeNode*root)
{
    if(!root) return;
    tem.push_back(sumNode(root));
    dfs(root->left);
    dfs(root->right);
}
vector<int> findFrequentTreeSum(TreeNode* root) {
    dfs(root);
    map<int,int>mp;
    int cmax=-1;
    for(auto m:tem)
    {
        mp[m]++;
        cmax=max(cmax,mp[m]);
    }
    vector<int>ans;
    for(auto n:mp)
        if(n.second==cmax) ans.push_back(n.first);   
    return ans;
}
int main()
{

}