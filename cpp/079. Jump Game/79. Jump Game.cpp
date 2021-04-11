/**
		Given an array of non-negative integers, you are initially positioned at the first index of the array.

		Each element in the array represents your maximum jump length at that position.

		Determine if you are able to reach the last index.

		For example:
		A = [2,3,1,1,4], return true.

		A = [3,2,1,0,4], return false.
		
	See 89. Jump Game II
	
*/
// pass 3
class Solution {
public:
    bool canJump(int A[], int n) {
		int i = 0;
		while(i < n) {
			if(i+A[i] >= n-1)
				return true;
			
			// find the next index
			int k = i;
			for(int j=i+1; j<=i+A[i]; ++j) {
				if(j+A[j] > k+A[k])
					k = j;
			}
			
			if(k <= i)
				return false;
			i = k;
		}
		
		return false;
    }
};


































// pass 2
// O(n^2)
class Solution {
public:
    bool canJump(int A[], int n) {
		// find the one which can jump the most
		int i = 0;
		while(i < n) {
			int next = i + A[i]; 
			// can jump [i...next]
			int nexti = i;
			for(int k=i; k<=next; ++k) {
				if(k >=n || A[k]+k >= n-1)
					return true;
				else if(A[k]+k > A[nexti]+nexti)
					nexti = k;
			}
			
			if(nexti <= i)
				break;
			i = nexti;
		}
		
		return i+A[i]>=n-1;
    }
};

































class Solution {
public:
	bool canJump(int A[], int n)
	{
		if(!n)
			return false;
		
		vector<bool> ary(n, false);
		ary[0] = true;
		for(int i=1; i<n; ++i)
			for(int j=0; j<i; ++j) {
				int nLen = i - j;
				if(ary[j] && A[j]>=nLen) {
					ary[i] = true;
					break;
				}
			}
		return ary[n-1];
	}
};


