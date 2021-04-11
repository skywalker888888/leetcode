/**
		Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

		Note:
		Elements in a triplet (a,b,c) must be in non-descending order. (ie, a <= b <= c)
		The solution set must not contain duplicate triplets.
			For example, given array S = {-1 0 1 2 -1 -4},

			A solution set is:
			(-1, 0, 1)
			(-1, -1, 2)
*/
// pass 3
class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
		sort(num.begin(), num.end());
		vector<vector<int> > res;
		for(int i=0; i<num.size(); ++i) {
			for(int j=i+1, k=num.size()-1; j<k; ) {
				int val = num[i] + num[j] + num[k];
				if(!val) {
					vector<int> item;
					item.push_back(num[i]);
					item.push_back(num[j]);
					item.push_back(num[k]);
					sort(item.begin(), item.end());
					res.push_back(item);
					++j;
					--k;
				}
				else if(val > 0) {
					--k;
				} else {
					++j;
				}
			}
		}
		sort(res.begin(), res.end());
		vector<vector<int> >::iterator itrEnd = unique(res.begin(), res.end());
		vector<vector<int> > result;
		result.insert(result.end(), res.begin(), itrEnd);
		return result;
    }
};


































// pass 2
class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
		sort(num.begin(), num.end());
		int n = num.size();
		vector<vector<int> > res;
		if(n < 3)
			return res;
		
		for(int i=0; i<n; ++i)
			for(int j=i+1, k=n-1; j<k;) {
				int val = num[i] + num[j] + num[k];
				if(!val) {
					vector<int> item;
					item.push_back(num[i]);
					item.push_back(num[j]);
					item.push_back(num[k]);
					sort(item.begin(), item.end());
					res.push_back(item);
					--k;
					++j;
				} else if(val > 0)
					--k;
				else
					++j;
			}
		sort(res.begin(), res.end());
		vector<vector<int> >::iterator itrEnd = unique(res.begin(), res.end());
		vector<vector<int> > result;
		result.insert(result.end(), res.begin(), itrEnd);
		return result;
    }
};













































class Solution {
public:
	/**
		O(n^2)
	*/
	vector<vector<int> > threeSum(vector<int> &num)
	{
		vector<vector<int> > result;
		int n = num.size();
		
		if(n < 3)
			return result;
		sort(num.begin(), num.end());
		
		set<vector<int> > res_set;
		for(int i=0; i<n; ++i)
			for(int j=i+1, k=n-1; j<k;)
			{
				int sum = num[i] + num[j] + num[k];
				if(sum < 0)
					++j;
				else if(sum > 0)
					--k;
				else
				{
					vector<int> item;
					item.push_back(num[i]);
					item.push_back(num[j]);
					item.push_back(num[k]);
					sort(item.begin(), item.end());
					res_set.insert(item);
					++j;
					--k;
				}
			}
			
		result.resize(res_set.size());
		copy(res_set.begin(), res_set.end(), result.begin());
		return result;
	}
};

