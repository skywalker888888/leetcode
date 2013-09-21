/**
		Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
		The same repeated number may be chosen from C unlimited number of times
		Note:
		All numbers (including target) will be positive integers.
		Elements in a combination (a1, a2, .. , ak) must be in non-descending order. (ie, a1 <= a2 <= ... <= ak).
		The solution set must not contain duplicate combinations.
		For example, given candidate set 2,3,6,7 and target 7, 
		A solution set is: 
		[7] 
		[2, 2, 3] 
*/
// pass 3
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
		
		vector<vector<int> > result;
		combinationSum(candidates, 0, target, result);
		return result;
    }
	
	void combinationSum(vector<int> &candidates, int index, int target, vector<vector<int> > &result) {
		int n = candidates.size();
		if(index>=n) {
			return;
		}
		while(index<candidates.size() && target>=candidates[index]) {
			vector<int> item;
			for(int i=1; target>=candidates[index]*i; ++i) {
				item.push_back(candidates[index]);
				if(target == candidates[index]*i) {
					result.push_back(item);
				} else if(index+1<n) {
					vector<vector<int> > res;
					combinationSum(candidates, index+1, target-candidates[index]*i, res);
					for(int j=0; j<res.size(); ++j) {
						vector<int> i2 = item;
						i2.insert(i2.end(), res[j].begin(), res[j].end());
						result.push_back(i2);
					}
				}
			}
			++index;
		}
	}
};











































// pass 2
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    	sort(candidates.begin(), candidates.end());
		
		vector<vector<int> > result;
		
		combinationSum(candidates, 0, target, result);
		
		return result;
    }
	
	void combinationSum(vector<int> &candidates, int index, int target, vector<vector<int> > &result) {
		if(target <= 0)
			return;
		
		while(index<candidates.size() && target>=candidates[index]) {
			for(int i=1; candidates[index]*i<=target; ++i) {
				vector<int> pre(i, candidates[index]);
				vector<vector<int> > res;
				if(target == candidates[index]*i) {
					result.push_back(pre);
				} else {
					combinationSum(candidates, index+1, target-candidates[index]*i, res);
					for(int j=0; j<res.size(); ++j) {
						vector<int> item = pre;
						item.insert(item.end(), res[j].begin(), res[j].end());
						result.push_back(item);
					}
				}
			}
			++index;
		}
	}
};




































class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<int> > result;
		int n = candidates.size();
		if(!n)
			return result;
		sort(candidates.begin(), candidates.end());
		vector<int> selection(n, 0);
		vector<int> copies(n, 0);
		int value = target;
		int index = 0;
		selection[index] = 0;
		copies[index] = 1;
		value -= candidates[selection[index]] * copies[index];
		while(true) {
			if(selection[0] >= n)
				break;
			if(value == 0){
				addResultItem(candidates, selection, copies, index, result);
				value += candidates[selection[index]] * copies[index];
				if(selection[index] == n-1) {
					if(!index)
						break;
					// 
					--index;
					++copies[index];
					value -= candidates[selection[index]];
				} else {
					++selection[index];
					copies[index] = 1;
					value -= candidates[selection[index]];
				}
			} else if(value > 0) {
				if(selection[index] == n-1) {
					++copies[index];
					value -= candidates[selection[index]];
				} else {
					++index;
					selection[index] = selection[index-1] +1 ;
					copies[index] = 1;
					value -= candidates[selection[index]];
				}
			} else {
				value += candidates[selection[index]] * copies[index];
				if(selection[index] >= n-1)
					if(!index)
						break;
					else {
						--index;
						++copies[index];
						value -= candidates[selection[index]];
					}
				else if(copies[index] == 1) {
					// go back
					if(!index)
						break;
					else {
						--index;
						++copies[index];
						value -= candidates[selection[index]];
					}
				} else {
					++selection[index];
					copies[index] = 1;
					value -= candidates[selection[index]];
				}
			}
		}
		return result;
	}
	void addResultItem(vector<int> &candidates, vector<int>& selection, vector<int>& copies, int index, vector<vector<int> > &result)
	{
		vector<int> item;
		for(int i=0; i<=index; ++i)
			for(int j=0; j<copies[i]; ++j)
				item.push_back(candidates[selection[i]]);
		result.push_back(item);
	}
};





class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		int n = candidates.size();
		vector<vector<int> > result;
		vector<int> item;
		combinationSumSub(candidates, target, 0, result, item);
		return result;
	}
	void combinationSumSub(vector<int> &candidates, int target, int index, vector<vector<int> > &result, vector<int> item) {
		int n = candidates.size();
		if(index >= n)
			return;
		sort(candidates.begin(), candidates.end());
		if(!target) {
			result.push_back(item);
			return;
		}
		vector<int> item2 = item;
		int nCopies = 1;
		while(target - nCopies*candidates[index]>=0) {
			if(target - nCopies*candidates[index] == 0) {
				item2.push_back(candidates[index]);
				result.push_back(item2);
				break;
			} else {
				item2.push_back(candidates[index]);
				combinationSumSub(candidates, target - nCopies*candidates[index], index+1, result, item2);
				++nCopies;
			}
		}
		// skip the current index and go to next 
		combinationSumSub(candidates, target, index+1, result, item);
	}
};
