/**
		Suppose a sorted array is rotated at some pivot unknown to you beforehand.

		(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

		You are given a target value to search. If found in the array return its index, otherwise return -1.

		You may assume no duplicate exists in the array.
		
		See also:
			52. Search in Rotated Sorted Array II

*/
// pass 3
class Solution {
public:
    int search(int A[], int n, int target) {
		int s = 0;
		int e = n-1;
		while(s <= e) {
			int m = (s + e)/2;
			if(A[m] == target) {
				return m;
			} else if(A[s] > A[m]) {
				if(target < A[m])
					e = m - 1;
				else if(target > A[e])
						e = m - 1;
					else
						s = m + 1; 
			} else {
				if(target > A[m])
					s = m + 1;
				else if(target < A[s])
					s = m + 1;
				else
					e = m - 1;
			}
		}
		
		return -1;
    }
};

class Solution {
public:
    int search(int A[], int n, int target) {
		int s = 0;
		int e = n-1;
		while(s <= e) {
			int m = (s + e)/2;
			if(A[m] == target) {
				return m;
			} else if(A[s] > A[m]) {
				if(target > A[m])
					if(target > A[e])
						e = m - 1;
					else
						s = m + 1;
				else
					e = m - 1;
			} else {
				if(target < A[m])
					if(target < A[s])
						s = m + 1;
					else
						e = m - 1;
				else
					s = m + 1;
			}
		}
		
		return -1;
    }
};





































// pass 2
class Solution {
public:
    int search(int A[], int n, int target) {
		int s = 0;
		int e = n-1;
		while(s <= e) {
			int m = (s + e)/2;
			if(target == A[m])
				return m;
			else if(A[s] > A[m]) {
				if(target > A[m])
					if(target > A[e])
						e = m - 1;
					else
						s = m + 1;
				else
					e = m - 1;
			} else {
				if(target < A[m])
					if(target < A[s])
						s = m + 1;
					else
						e = m -1;
				else
					s = m + 1;
					
			}
		}
		
		return -1;
    }
};










































class Solution {
public:
	int search(int A[], int n, int target)
	{
		int s = 0;
		int e = n - 1;
		
		while(s <= e)
		{
			int m = (s + e)/2;
			
			if(target == A[m])
				return m;
			else if(A[e] >= A[m])
			{
				// right side ordered and left side has the pivot
				if(target > A[m])
					if(target <= A[e])
						s = m + 1;
					else
						e = m - 1;
				else
					e = m - 1;
			}
			else 
			{
				// left side is ordered and the right side has the pivot
				if(target > A[m])
					s = m + 1;
				else
					if(target >= A[s])
						e = m - 1;
					else
						s = m + 1;
			}
		}
		
		return -1;
	}
};

