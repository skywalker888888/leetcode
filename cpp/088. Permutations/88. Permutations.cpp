/**
		Given a collection of numbers, return all possible permutations.

		For example,
		[1,2,3] have the following permutations:
		[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
*/
// pass 3
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
		vector<vector<int> > result;
		permute(num, 0, result);
		return result;
    }
	
	void permute(vector<int> &num, int i, vector<vector<int> > &result) {
		if(i >= num.size()) {
			result.push_back(num);
		} else {
			for(int j=i; j<num.size(); ++j) {
				swap(num[i], num[j]);
				permute(num, i+1, result);
				swap(num[i], num[j]);
			}
		}
	}
};









































// pass 2
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
		vector<vector<int> > result;
		permute(num, 0, result);
		
		return result;
    }
	
    void permute(vector<int> &num, int i, vector<vector<int> > &result) {
		if(i >= num.size()) 
			result.push_back(num);
		else {
			for(int k=i; k<num.size(); ++k) {
				swap(num[i], num[k]);
				permute(num, i+1, result);
				swap(num[i], num[k]);
			}
		}
	}
};





































class Solution {
public:
	vector<vector<int> > permute(vector<int> &num)
	{
		vector<vector<int> > result;
		int n = num.size();
		if(!n)
			return result;
		permute(0, num, result);
		return result;
	}
	void permute(int i, vector<int> &num, vector<vector<int> >& result)
	{
		int n = num.size();
		if(i >= n-1)
		{
			result.push_back(num);
			return;
		}
		permute(i+1, num, result);
		for(int k=i+1; k<n; ++k)
		{
			vector<int>::iterator itr = num.begin() + i;
			vector<int>::iterator itrnext = num.begin() + k;
			swap(num[i], num[k]);
			permute(i+1, num, result);
			swap(num[i], num[k]);
		}
	}
};






