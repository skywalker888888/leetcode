/**
		Given a collection of numbers that might contain duplicates, return all possible unique permutations.

		For example,
		[1,1,2] have the following unique permutations:
		[1,1,2], [1,2,1], and [2,1,1].
*/
// pass 3
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
    	sort(num.begin(), num.end());
		vector<bool> used(num.size(), false);
		
		vector<vector<int> > result;
		result = permuteUnique(num, used);
		return result;
    }
	
    vector<vector<int> > permuteUnique(vector<int> &num, vector<bool> &used) {
		vector<vector<int> > result;
		int n = num.size();
		int last_i = -1;
		for(int i=0; i<n; ++i) {
			if(!used[i] &&(last_i==-1||num[last_i]!=num[i])) {
				used[i] = true;
				last_i = i;
				
				vector<vector<int> > res = permuteUnique(num, used);
				for(int j=0; j<res.size(); ++j) {
					vector<int> item;
					item.push_back(num[i]);
					item.insert(item.end(), res[j].begin(), res[j].end());
					result.push_back(item);
				}
				used[i] = false;
			}
		}
		if(!result.size())
			result.resize(1);
		return result;
	}
};
















































// pass 2
/*
	之前看了peking2大牛写得一道类似的题，自己跟着用例子跑了一遍他的程序，算是半
	学会这个基本思路。
	用例子来说就是
	假如input是11122
	look at the first sub-problem: pick one as the first number and generate all
	all permutation with this num as the first number.
	我们第一次pick的是1，并生成了所有以1开头的permutation，第二次我们遇到的还是1, 如果我们这次还是以这个1为开头(why? because the first number is 1, and everything left is also the same)，那么这次我们所有这次生成的序列都会和上一次重复.If you still not understand, run it step by step by hand for one time.
*/
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
    	vector<vector<int> > result;
        int n = num.size();
		if(!n)
			return result;
			
		sort(num.begin(), num.end());
		vector<bool> used(n, false);
		
		result = permuteUnique(num, used);
		return result;
    }
	
    vector<vector<int> > permuteUnique(vector<int> &num, vector<bool> &used) {
		vector<vector<int> > result;
		int n = num.size();
		
		int lastIndex = -1;
		for(int i=0; i<n; ++i)
			if(!used[i] && (lastIndex==-1 || num[lastIndex]!=num[i])) {
				lastIndex = i;
				used[i] = true;
				vector<vector<int> > res1 = permuteUnique(num, used);
				for(int j=0; j<res1.size(); ++j) {
					vector<int> item;
					item.push_back(num[i]);
					item.insert(item.end(), res1[j].begin(), res1[j].end());
					result.push_back(item);
				}
				used[i] = false;
			}
			
		if(!result.size()) 
			result.resize(1);
		
		return result;
	}
};















































class Solution {
public:
	vector<vector<int> > permuteUnique(vector<int> &num) {
		vector<vector<int> > result;
		int n = num.size();
		if(!n)
			return result;
		sort(num.begin(), num.end());
		
		vector<bool> positionused(n, false);
		vector<int> item(n);
		permuteUnique(0, num, result, positionused, item);
		return result;
	}
	
	void permuteUnique(int i, vector<int> &num, vector<vector<int> >& result, vector<bool> &positionused, vector<int> item) {
		int n = num.size();
		
		if(i >= n) {
			result.push_back(item);
			return;
		}
		
		int count = 1;
		for(int k=i+1; k<n; ++k)
			if(num[k] != num[i])
				break;
			else 
				++count;

		// find all possible count positions for these same values
		vector<int> positions(count, -1);
		int index = 0;
		while(true) {
			if(index == count-1) {
				int nNextPos = 0;
				if(index-1 >= 0)
					nNextPos = positions[index-1] + 1;
				for(int k=nNextPos; k<n; ++k)
					if(!positionused[k]) {
						positions[index] = k;
						positionused[k] = true;
						item[k] = num[i];
						permuteUnique(i+count, num, result, positionused, item);
						positionused[k] = false;
					}
				positions[index] = n;
			}
			bool bFoundSpace = false;
			
			int ind = positions[index];
			if(ind>=0 && ind<n)
				positionused[ind] = false;
			
			if(ind<0 && index>0)
				ind = positions[index-1];
			for(int k=ind+1; k<n; ++k)
				if(!positionused[k]) {
					bFoundSpace = true;
					positions[index] = k;
					positionused[k] = true;
					item[k] = num[i];
					++index;
					positions[index] = -1;
					break;
				}
			if(!bFoundSpace) {
				// roll back
				--index;
				if(index<0)
					break;
			}
		}
	}
};

