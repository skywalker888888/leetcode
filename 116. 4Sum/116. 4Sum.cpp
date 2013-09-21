#include "stdafx.h"

#include <vector>
#include <algorithm>
using namespace std;

/**
		Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
		Note:
		Elements in a quadruplet (a,b,c,d) must be in non-descending order. (ie, a ? b ? c ? d)
		The solution set must not contain duplicate quadruplets.
			For example, given array S = {1 0 -1 0 -2 2}, and target = 0.

			A solution set is:
			(-1,  0, 0, 1)
			(-2, -1, 1, 2)
			(-2,  0, 0, 2)
*/
// pass 2
// Time: O(n^2 log n)
// Space: O(n^2)
class Solution {
	struct TwoSum {
		int pos1;
		int pos2;
		int value;
		TwoSum(int i, int j, int val) : pos1(i), pos2(j), value(val) {}
	};
	class TwoSumIncreasing {
	public:
		bool operator()(const TwoSum &t1, const TwoSum &t2) {
			if(t1.value == t2.value) {
				if(t1.pos1 == t2.pos1)
					return t1.pos2 < t2.pos2;
				return t1.pos1 < t2.pos1;
			}
			return t1.value < t2.value;
		}
	};
public:
	int find_left_index(vector<TwoSum> &values, int s, int e, int target) {
		int result = -1;
		while(s <= e) {
			int m = (s + e) / 2;
			if(target == values[m].value) {
				result = m;
				e = m - 1;
			} else if(target > values[m].value)
				s = m + 1;
			else 
				e = m - 1;
		}
		return result;
	}
	int find_right_index(vector<TwoSum> &values, int s, int e, int target) {
		int result = -1;
		while(s <= e) {
			int m = (s + e) / 2;
			if(target == values[m].value) {
				result = m;
				s = m + 1;
			} else if(target > values[m].value)
				s = m + 1;
			else 
				e = m - 1;
		}
		return result;
	}
    vector<vector<int> > fourSum(vector<int> &num, int target) {
		vector<vector<int> > result;
		int n = num.size();
		if(n < 4)
			return result;
			
		// O(n^2)
		vector<TwoSum> twoSums;
		for(int i=0; i<n; ++i)
			for(int j=i+1; j<n; ++j)
				twoSums.push_back(TwoSum(i, j, num[i]+num[j]));
		// O(n^2 log n)
		sort(twoSums.begin(), twoSums.end(), TwoSumIncreasing());
		
		// O(n^2 log n)
		for(int i=0; i<twoSums.size()-1; ++i) { // n^2 
			int v1 = twoSums[i].value;
			int v2 = target - v1;
			int left = find_left_index(twoSums, i+1, twoSums.size()-1, v2); // log n
			int right = find_right_index(twoSums, i+1, twoSums.size()-1, v2); // log n
			for(int j=left; j>0 && j<=right; ++j) { // n^2 ??? 
				if(twoSums[i].pos1 == twoSums[j].pos1) continue;
				if(twoSums[i].pos1 == twoSums[j].pos2) continue;
				if(twoSums[i].pos2 == twoSums[j].pos1) continue;
				if(twoSums[i].pos2 == twoSums[j].pos2) continue;
				vector<int> item;  // n  at most. because there are n positions only
				item.push_back(num[twoSums[i].pos1]);
				item.push_back(num[twoSums[i].pos2]);
				item.push_back(num[twoSums[j].pos1]);
				item.push_back(num[twoSums[j].pos2]);
				sort(item.begin(), item.end());
				result.push_back(item);
			}
		}
		
		// O(n^2 log n)
		sort(result.begin(), result.end());
		vector<vector<int> >::iterator itrEnd = unique(result.begin(), result.end());
		
		// O(n^2)
		vector<vector<int> > res;
		res.insert(res.end(), result.begin(), itrEnd); 
		return res;
	}
};



// Time: O(n^3)
// Space: O(n) 
class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
		vector<vector<int> > result;
		int n = num.size();
		//map<vector<int>, int> valcount;
		sort(num.begin(), num.end());
		
		vector<vector<int> > res1;
		// O(n^3)
		for(int i=0; i<n; ++i)
			for(int j=i+1; j<n; ++j)
				for(int k=j+1, m=n-1; k<m;) {
					int val = num[i] + num[j] + num[k] + num[m];
					if(val == target) {
						vector<int> item;
						item.push_back(num[i]);
						item.push_back(num[j]);
						item.push_back(num[k]);
						item.push_back(num[m]);
						sort(item.begin(), item.end());
						//++valcount[item];
						//if(valcount[item] < 2) 
						//	result.push_back(item);
						res1.push_back(item);
						++k;
						--m;
					} else if(val < target)
						++k;
					else
						--m;
				}
		// O(n^2)
		sort(res1.begin(), res1.end());
		// O(n)
		vector<vector<int> >::iterator itrend = unique(res1.begin(), res1.end());
		// O(n)
		result.insert(result.end(), res1.begin(), itrend);
		return result;
    }
};








































struct ValPair {
	int val;
	int left;
	int right;
	
	ValPair(int v, int l, int r) : val(v), left(l), right(r) {}
};

bool ValPairCompareLess(ValPair first, ValPair second) {
	return first.val < second.val;
}
struct ResultIndices {
	int i1;
	int i2;
	int i3;
	int i4;
	ResultIndices(int v1, int v2, int v3, int v4) {
		vector<int> inds;
		inds.push_back(v1);
		inds.push_back(v2);
		inds.push_back(v3);
		inds.push_back(v4);
		sort(inds.begin(), inds.end());
		i1 = inds[0];
		i2 = inds[1];
		i3 = inds[2];
		i4 = inds[3];
	}
};

class ResultIndicesEqual {
public:
	bool	operator() (ResultIndices first, ResultIndices second) {
		return first.i1==second.i1 && first.i2==second.i2 && first.i3==second.i3 && first.i4==second.i4;
	};
};

bool ResultIndicesLess(ResultIndices first, ResultIndices second) {
	if(first.i1 < second.i1)
		return true;
	else if(first.i1 > second.i1)
		return false;
	if(first.i2 < second.i2)
		return true;
	else if(first.i2 > second.i2)
		return false;
	if(first.i3 < second.i3)
		return true;
	else if(first.i3 > second.i3)
		return false;
	if(first.i4 < second.i4)
		return true;
	else if(first.i4 > second.i4)
		return false;
	return false;
}

bool ResultIndicesEqual(ResultIndices first, ResultIndices second) {
	bool bless = ResultIndicesLess(first, second);
	bool bgreater = ResultIndicesLess(second, first);
	return !bless && !bgreater;
}

class Solution {
public:
	/**
		O(n^2 lgn). First sort all pairs based on their sum, then do a binary search. 
	*/
	vector<vector<int> > fourSum(vector<int> &num, int target) {
		vector<vector<int> > result;
		vector<ResultIndices> resultinds;
		int n = num.size();
		if(n < 4)
			return result;
		vector<ValPair> pairs;
		for(int i=0; i<n; ++i)
			for(int j=i+1; j<n; ++j)
				pairs.push_back(ValPair(num[i]+num[j], i, j));
		sort(pairs.begin(), pairs.end(), ValPairCompareLess);
		vector<ValPair>::iterator itr = pairs.begin();
		while(itr < pairs.end()) {
			int val = target - (*itr).val;
			pair<vector<ValPair>::iterator,vector<ValPair>::iterator> rnge = equal_range(itr+1, pairs.end(), ValPair(val, 0, 0), ValPairCompareLess);
			for(vector<ValPair>::iterator i=rnge.first; i<rnge.second; ++i) {
				ResultIndices it((*itr).left, (*itr).right, (*i).left, (*i).right);
				if(it.i1!=it.i2 && it.i2!=it.i3 && it.i3!=it.i4)
					resultinds.push_back(it);
			}
			++itr;
		}
		
		//
		sort(resultinds.begin(), resultinds.end(), ResultIndicesLess);
		vector<ResultIndices>::iterator itrlast = unique(resultinds.begin(), resultinds.end(), ResultIndicesEqual);
		
		for(vector<ResultIndices>::iterator i = resultinds.begin(); i<itrlast; ++i) {
			vector<int> item;
			item.push_back(num[(*i).i1]);
			item.push_back(num[(*i).i2]);
			item.push_back(num[(*i).i3]);
			item.push_back(num[(*i).i4]);
			sort(item.begin(), item.end());
			if(find(result.begin(), result.end(), item)== result.end())
				result.push_back(item);
		}
		
		return result;
	}
};



class Solution {
public:
	/**
		Time: O(n^3). 
		Space: O(1)
	*/
	vector<vector<int> > fourSum(vector<int> &num, int target) {
		int n = num.size();
		sort(num.begin(), num.end());
		
		set<vector<int> > res_set;
		vector<vector<int> > result;
		if(n < 4)
			return result;
		for(int i=0; i<n; ++i)
			for(int j=i+1; j<n; ++j)
				for(int k=j+1, l=n-1; k<l;) {
					int sum = num[i] + num[j] + num[k] + num[l];
					if(sum > target)
						--l;
					else if(sum < target)
						++k;
					else if(sum == target) {
						vector<int> item;
						item.push_back(num[i]);
						item.push_back(num[j]);
						item.push_back(num[k]);
						item.push_back(num[l]);
						sort(item.begin(), item.end());
						res_set.insert(item);
						++k;
						--l;
					}
				}
		result.resize(res_set.size());		
		copy(res_set.begin(), res_set.end(), result.begin());
		return result;
	}
};





//============================================================================
// 4Sum
// Given an array S of n integers, are there elements a, b, c, and d in S such
// that a + b + c + d = target?
// Find all unique quadruplets in the array which gives the sum of target.
// Note:
// Elements in a quadruplet (a,b,c,d) must be in non-descending order.
// (ie, a ≤ b ≤ c ≤ d)
// The solution set must not contain duplicate quadruplets.
// For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
// A solution set is:
// (-1,  0, 0, 1)
// (-2, -1, 1, 2)
// (-2,  0, 0, 2)
// https://github.com/anson627/leetcode/blob/master/4Sum/4Sum.cpp
//============================================================================

class Solution {
public:
	struct TwoSum{
	public:
		TwoSum(int idx1, int idx2, int v) :
			index1(idx1), index2(idx2), value(v) {}
	public:
		int index1;
		int index2;
		int value;
	};

	struct increaing {
		bool operator() (TwoSum ts1, TwoSum ts2) {
			if (ts1.value == ts2.value){
				if (ts1.index1 == ts2.index1) return (ts1.index2 < ts2.index2);
				else return (ts1.index1 < ts2.index1);
			}
			else
				return (ts1.value < ts2.value);
		}
	};
    int find_start_index(vector<TwoSum>& twoSums, int begin, int end, int val){
        while (begin <= end) {
            int mid = begin + (end - begin) / 2;
            if (twoSums[mid].value >= val) end = mid - 1;
            else begin = mid + 1;
        }
        return end + 1;
    };

    int find_end_index(vector<TwoSum>& twoSums, int begin, int end, int val){
        while (begin <= end) {
            int mid = begin + (end - begin) / 2;
            if (twoSums[mid].value <= val) begin = mid + 1;
            else end = mid - 1;
        }
        return begin - 1;
    }

    vector<vector<int> > fourSum(vector<int> &num, int target) {
        // calculate sum for every two elements and sort
        vector<TwoSum> twoSums;
        for (size_t i = 0; i < num.size(); i++)
			for (size_t j = i + 1; j < num.size(); j++)
                twoSums.push_back(TwoSum(i, j, num[i] + num[j]));
        sort(twoSums.begin(), twoSums.end(), increaing());

        vector<vector<int> > result;
        for (size_t i = 0; i < twoSums.size(); i++){
            size_t begin, end;
            int val = target - twoSums[i].value;

            begin = find_start_index(twoSums, i + 1, twoSums.size() - 1, val);
            end = find_end_index(twoSums, i + 1, twoSums.size() - 1, val);

            for (size_t j = begin; j <= end; j++) {
                if (twoSums[j].index1 == twoSums[i].index1) continue;
                if (twoSums[j].index2 == twoSums[i].index1) continue;
                if (twoSums[j].index1 == twoSums[i].index2) continue;
                if (twoSums[j].index2 == twoSums[i].index2) continue;

                vector<int> tmp;
                tmp.push_back(num[ twoSums[i].index1]);
                tmp.push_back(num[ twoSums[i].index2]);
                tmp.push_back(num[ twoSums[j].index1]);
                tmp.push_back(num[ twoSums[j].index2]);
                sort(tmp.begin(), tmp.end());

                if (find(result.begin(), result.end(), tmp) == result.end())
                    result.push_back(tmp);
            }
        }
        return result;
    };
};

