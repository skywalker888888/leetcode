/**
		Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
		Each number in C may only be used once in the combination.
		Note:
		All numbers (including target) will be positive integers.
		Elements in a combination (a1, a2, ... , ak) must be in non-descending order. (ie, a1 <= a2 <= ... <= ak).
		The solution set must not contain duplicate combinations.
		For example, given candidate set 10,1,2,7,6,1,5 and target 8, 
		A solution set is: 
		[1, 7] 
		[1, 2, 5] 
		[2, 6] 
		[1, 1, 6] 
*/
// pass 3
class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
    	sort(num.begin(), num.end());
		vector<vector<int> > result;
		combinationSum2(num, target, 0, result);
		return result;
    }
	void combinationSum2(vector<int> &num, int target, int index, vector<vector<int> > &result) {
		int n = num.size();
		if(index >= n)
			return;
		
		if(target < num[index])
			return;
			
		if(target == num[index]) {
			vector<int> item(1, target);
			result.push_back(item);
			return;
		}
		if(index+1 >= n)
			return;
			
		vector<vector<int> > r;
		combinationSum2(num, target-num[index], index+1, r);
		for(int i=0; i<r.size(); ++i) {
			vector<int> item(1, num[index]);
			item.insert(item.end(), r[i].begin(), r[i].end());
			result.push_back(item);
		}
		
		//
		int i=index+1;
		while(i<n && num[i]==num[index])
			++i;
		if(i<n)
			combinationSum2(num, target, i, result);
	}
};













































// pass 2
class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        sort(num.begin(), num.end());
		vector<vector<int> > result;
		combinationSum2(num, 0, target, result);
		return result;
    }
    void combinationSum2(const vector<int> &num, int index, int target, vector<vector<int> > &result) {
		if(index>=num.size() || target<=0 || target<num[index])
			return;
		if(target == num[index]) 
			result.push_back(vector<int>(1, num[index]));
		else {
			vector<vector<int> > res;
			combinationSum2(num, index+1, target-num[index], res);
			for(int i=0; i<res.size(); ++i) {
				vector<int> item(1, num[index]);
				item.insert(item.end(), res[i].begin(), res[i].end());
				result.push_back(item);
			}
		}
		++index;
		while(index<num.size() && num[index]==num[index-1])
			++index;
			
		combinationSum2(num, index, target, result);
	}
};


































class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target);
	
private:
	void	addNewResult(vector<vector<int> > &result, const vector<int> &num, const vector<int>& selection, int index);
	int		getNextPosition(const vector<int> &num, const vector<int>& selection, const vector<bool> &skipSameItem, int index);
};


/**
	DFS the directed graph
 */
vector<vector<int> > Solution::combinationSum2(vector<int> &num, int target)
{
	vector<vector<int> > result;
	int n = num.size();
	if(!n)
		return result;
		
	sort(num.begin(), num.end());
		
	vector<int> selection(n, -1);
	vector<bool> skipSameItem(n, false);
	int index = 0;
	int value = target;
	selection[index] = 0;
	
	value-= num[selection[index]];
	
	bool bSkipSameItem = false;
	
	// Start DFS
	while(true)
	{
		if(selection[0] >= n)
			break;
		
		bool bRollBack = false;
		if(!value)
		{
			// add list to result
			addNewResult(result, num, selection, index);
			bRollBack = true;
		}
		else if(value > 0)
		{
			int nextpos = getNextPosition(num, selection, skipSameItem, index);
			if(nextpos >= n)
			{
				bRollBack = true;
			}
			else
			{
				++index;
				selection[index] = nextpos;
				value-= num[selection[index]];
				
				if(num[selection[index-1]] == num[selection[index]])
					skipSameItem[index] = skipSameItem[index-1];
				else 
					skipSameItem[index] = false;
			}
		}
		else
			bRollBack = true;
		
		while(bRollBack)
		{
			bRollBack = false;
			// selection[index] is not valid anymore. 
			value += num[selection[index]];
			
			for(int i=index; i>=0 && num[selection[i]]==num[selection[index]]; --i)
				skipSameItem[i] = true;

			char ch = num[selection[index]];
			// try next one
			int nextpos = getNextPosition(num, selection, skipSameItem, index);
			if(nextpos >= n)
			{
				if(!index)
					selection[index] = nextpos; // quit the 
				else
				{
					--index;
					if(index < 0)
					{
						selection[0] = n;
						break;
					}
					bRollBack = true;
				}
			}
			else
			{
				//++index;
				selection[index] = nextpos;
				if(ch != num[selection[index]])
					skipSameItem[index] = false;
				value-= num[selection[index]];
			}
		}
	}
	return result;
}


void Solution::addNewResult(vector<vector<int> > &result, const vector<int> &num, const vector<int>& selection, int index)
{
	vector<int> item;
	for(int i=0; i<=index; ++i)
		item.push_back(num[abs(selection[i])]);
		
	result.push_back(item);
}

int Solution::getNextPosition(const vector<int> &num, const vector<int>& selection, const vector<bool> &skipSameItem, int index)
{
	int n = num.size();
	int nextpos = selection[index];
	if(skipSameItem[index])
	{
		// can not select the next same item anymore
		while(nextpos<n && num[nextpos]==num[selection[index]])
			++nextpos;
		
	}
	else
		++nextpos;

	return nextpos;
}

int main(int argc, char **argv)
{
	Solution sol;
	//vector<vector<int> > combinationSum2(vector<int> &num, int target);
	vector<int> num;
	num.push_back(1);
	num.push_back(1);
	int target = 1;
	
	sol.combinationSum2(num, target);
	
}



