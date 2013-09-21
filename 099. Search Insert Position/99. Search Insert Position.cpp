/**
		Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

		You may assume no duplicates in the array.

		Here are few examples.
		[1,3,5,6], 5 ¡ú 2
		[1,3,5,6], 2 ¡ú 1
		[1,3,5,6], 7 ¡ú 4
		[1,3,5,6], 0 ¡ú 0
*/
// pass 3
class Solution {
public:
    int searchInsert(int A[], int n, int target) {
		int s = 0;
		int e = n-1;
		while(s <= e) {
			int m = (s+e)/2;
			if(target == A[m])
				return m;
			else if(target > A[m])
				s = m+1;
			else
				e = m-1;
		}
		return s;
    }
};




























// pass 2
class Solution {
public:
    int searchInsert(int A[], int n, int target) {
		int start = 0;
		int finish = n-1;
		while(start <= finish) {
			int mid = (start+finish)/2;
			if(A[mid] == target)
				return mid;
			else if(target > A[mid])
				start = mid+1;
			else
				finish = mid-1;
		}
		
		return start;
    }
};









































class Solution {
public:
    int searchInsert(int A[], int n, int target);
};


int Solution::searchInsert(int A[], int n, int target)
{
	if(!n)
		return 0;
	
	int s = 0;
	int e = n-1;
	
	while(s <= e)
	{
		int m = (s + e)/2;
		
		if(A[m] == target)
			return m;
		else if(target > A[m])
			s = m + 1;
		else
			e = m - 1;
	}
	
	return s;
}


