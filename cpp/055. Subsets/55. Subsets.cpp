/**
		Given a set of distinct integers, S, return all possible subsets.
		Note:
		Elements in a subset must be in non-descending order.
		The solution set must not contain duplicate subsets.
		For example,
		If S = [1,2,3], a solution is:

		[
		  [3],
		  [1],
		  [2],
		  [1,2,3],
		  [1,3],
		  [2,3],
		  [1,2],
		  []
		]
		
		see also: 42. Subsets II
*/
// pass 3
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
    	sort(S.begin(), S.end());
		int n = S.size();
		vector<vector<vector<int> > > M(2);
		
        vector<int> item;
		M[0].push_back(item);
		int flag = 1;
		
		for(int len=1; len<=S.size(); ++len) {
			int value = S[len-1];
			for(int i=0; i<M[!flag].size(); ++i) {
				item = M[!flag][i];
				M[flag].push_back(item);
				item.push_back(value);
				M[flag].push_back(item);
			}
			M[!flag].clear();
			flag = !flag;
		}
		
		return M[!flag];
	}
};























// pass 2
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
		sort(S.begin(), S.end());

		vector<vector<int> > result;
		vector<vector<int> > result0;
		result0.push_back(vector<int>());
		result.push_back(vector<int>());
		for(int i=0; i<S.size(); ++i){
			result.clear();
			int val = S[i];
			for(int j=0; j<result0.size(); ++j){
				vector<int> item = result0[j];
				if(item.size())
					result.push_back(item);
				item.push_back(val);
				result.push_back(item);
			}
			result.push_back(vector<int>());
			result0 = result;
		}
		
		return result;
    }
};


// Time:  O(n^2)
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
		sort(S.begin(), S.end());
		
		vector<vector<int> > result;
		int n = S.size();
		if(n){
			vector<int> S1 = S;
			S1.resize(n-1);
			vector<vector<int> > res1 = subsets(S1);
			for(int i=0; i<res1.size(); ++i){
				vector<int> item = res1[i];
				if(item.size())
					result.push_back(item);
				item.push_back(S[n-1]);
				result.push_back(item);
			}
		}
		
		vector<int> null;
		result.push_back(null);
		return result;
    }
};




























class Solution {
public:
	vector<vector<int> > subsets(vector<int> &S)
	{
		vector<int> SS = S;
		sort(SS.begin(), SS.end());
		vector<vector<int> > result;
		
		
		int n = SS.size();
		if(n)
		{
			int nNum = SS[n-1];
			vector<int> S1 = SS;
			S1.resize(n-1);
			
			vector<vector<int> > res = subsets(S1);
			for(int i=0; i<res.size(); ++i)
			{
				vector<int> item = res[i];
				if(item.size())
					result.push_back(item);
					
				item.push_back(nNum);
				result.push_back(item);
			}
		}
		
		vector<int> null;
		result.push_back(null);
		return result;
	}
};

