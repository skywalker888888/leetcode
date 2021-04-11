/**
		Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
			For example, given array S = {-1 2 1 -4}, and target = 1.
			The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/
// pass 3
class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
    	int n = num.size();
		if(n < 3)
			return -1;
		sort(num.begin(), num.end());
		int result = num[0]+num[1]+num[2];
		for(int i=0; i<n; ++i)
			for(int j=i+1, k=n-1; j<k; ) {
				int val = num[i] + num[j] + num[k];
				if(abs(result-target) > abs(val-target))
					result = val;
                    
				if(target == val)
					return target;
				else if(target > val)
					++j;
				else
					--k;
			}
		return result;
    }
};








































// pass 2
class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
		int n = num.size();
		if(n < 3)
			return -1;
		sort(num.begin(), num.end());
		
		int result = num[0] + num[1] + num[2];
		
		for(int i=0; i<n; ++i)
			for(int j=i+1, k=n-1; j<k; ) {
				int val = num[i] + num[j] + num[k];
				if(abs(val-target) < abs(result-target))
					result = val;
				if(val == target)
					return val;
				else if(target > val)
					++j;
				else
					--k;
			}
		return result;
    }
};
















































class Solution {
public:
	int threeSumClosest(vector<int> &num, int target)
	{
		int n = num.size();
		if(n < 3)
			return -1;
		
		int ret = num[0] + num[1] + num[2];
		int mindiff = abs(target - ret);
		sort(num.begin(), num.end());
		for(int i=0; i<n; ++i)
			for(int j=i+1, k=n-1; j<k;) {
				int sum = num[i] + num[j] + num[k];
				if(abs(target - sum) < mindiff) {
					mindiff = abs(target - sum);
					ret = sum;
				}
				if(sum == target)
					return sum;
				else if(sum > target)
					--k;
				else
					++j;
			}
			
		return ret;
	}
};

