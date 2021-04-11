/**
		Given a collection of integers that might contain duplicates, S, return all possible subsets.

		Note:
		Elements in a subset must be in non-descending order.
		The solution set must not contain duplicate subsets.
		For example,
		If S = [1,2,2], a solution is:

		[
		  [2],
		  [1],
		  [1,2,2],
		  [2,2],
		  [1,2],
		  []
		]
		
		see also: 55. Subsets
*/
// pass 3
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
		sort(S.begin(), S.end());

		vector<vector<vector<int> > > M(2);
		M[0].push_back(vector<int>());
		int flag = 1;
		
		int i = 0;
		while(i < S.size()) {
			int j = i+1;
			while(j<S.size() && S[j]==S[i])
				++j;
			for(int k=0; k<M[!flag].size(); ++k) {
				vector<int> item = M[!flag][k];
				M[flag].push_back(item);
				
				for(int m=i; m<j; ++m) {
					item.push_back(S[i]);
					M[flag].push_back(item);
				}
			}
			M[!flag].clear();
			flag = !flag;
			i = j;
		}
		return M[!flag];
    }
};
































// pass 2
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        sort(S.begin(), S.end());
		vector<vector<int> > result = subsetsWithDup(0, S);
		return result;
    }
    vector<vector<int> > subsetsWithDup(const int i, vector<int> &S) {
		
		vector<vector<int> > result;
		if(i >= S.size()){
			result.resize(1);
			return result;
		}
		
        int j=i;
		for(; j<S.size()&&S[i]==S[j]; ++j);
		
		vector<vector<int> > res1(1);
		for(int k=i; k<j; ++k)
			res1.push_back(vector<int>(k-i+1, S[i]));	

		vector<vector<int> > res2 = subsetsWithDup(j, S);
		
		// concate S1 and S2
		for(int i=0; i<res1.size(); ++i)
			for(int j=0; j<res2.size(); ++j){
				vector<int> item;
				item.insert(item.end(), res1[i].begin(), res1[i].end());
				item.insert(item.end(), res2[j].begin(), res2[j].end());
				result.push_back(item);
			}
		return result;
	}
};



















class Solution
{
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S);
	
    vector<vector<int> > subsetsWithDup(int i, vector<int> &S);
	void				appendSubset(vector<int> &S, int i, int j, vector<vector<int> >& data);
};


vector<vector<int> > Solution::subsetsWithDup(vector<int> &S)
{
	sort(S.begin(), S.end());
	
	vector<vector<int> > result;
	if(!S.size())
		return result;
		
	result = subsetsWithDup(0, S);
	result.push_back(vector<int>());
	return result;
}

vector<vector<int> > Solution::subsetsWithDup(int i, vector<int> &S)
{
	vector<vector<int> > result;
	if(i >= S.size())
		return result;
	int num = S[i];
	int j;
	for(j=i; j<S.size() && S[j]==num; ++j) ;
	
	vector<vector<int> > res1;
	for(int k=i; k<j; ++k)
		appendSubset(S, i, k, res1);
		
	vector<vector<int> > res2 = subsetsWithDup(j, S);
	if(!res2.size())
		return res1;

	for(int i=0; i<res1.size(); ++i)
	{
		result.push_back(res1[i]);
	}
		
	for(int i=0; i<res1.size(); ++i)
		for(int j=0; j<res2.size(); ++j)
		{
			vector<int> nitem = res1[i];
			nitem.insert(nitem.end(), res2[j].begin(), res2[j].end());
			result.push_back(nitem);
		}
	
	for(int j=0; j<res2.size(); ++j)
	{
		result.push_back(res2[j]);
	}
	return result;
}


void Solution::appendSubset(vector<int> &S, int i, int j, vector<vector<int> >& data)
{
	vector<int> subset;
	for(int k=i; k<=j; ++k)
		subset.push_back(S[k]);
		
	data.push_back(subset);
}

