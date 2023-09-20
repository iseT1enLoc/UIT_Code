#include<iostream>
#include<vector>
using namespace std;
//apply to vector
vector<float> Merge_sen(vector<float>v1, vector<float>v2)
{
	vector<float>ans;
	int i, j, k;

	v1.push_back(v1[v1.size() - 1] + v2[v2.size() - 1]+1);
	v2.push_back(v1[v1.size() - 1] + v2[v2.size() - 1]+1);

	for (i = j = k=0; k < v1.size() + v2.size()-2; k++)
	{
		if (v1[i] < v2[j])
			ans.push_back(v1[i++]);
		else ans.push_back(v2[j++]);
	}
	return ans;
}
int main()
{
	vector<float>a = { 1,2,4,78,90,124 };
	

	vector<float>b = { 2,4,5,6,7,8,89,123 };
	
	vector<float>ans = Merge_sen(a, b);
	for (auto m : ans)
		cout << m << "\t";
}