/**
		Follow up for "Search in Rotated Sorted Array":
		What if duplicates are allowed?
		Would this affect the run-time complexity? How and why?
		Write a function to determine if a given target is in the array.
		
		Analysis:
			There will be affection.
			
		See also:
			101. Search in Rotated Sorted Array
			
*/
// pass 3
class Solution {
public:
    bool search(int A[], int n, int target) {
		int s = 0;
		int e = n-1;
		while(s <= e) {
			int m = (s+e)/2;
			if(A[m] == target)
				return true;
			else if(A[s] < A[m]) {
				if(target > A[m])
					s = m + 1;
				else if(target < A[s])
					s = m + 1;
				else
					e = m - 1;
			} else if(A[s] > A[m]) {
				if(target < A[m])
					e = m - 1;
				else if(target < A[s])
					s = m + 1;
				else
					e = m - 1;
			} else {
				++s;
			}
		}
		return false;
    }
};







































// pass 2
class Solution {
public:
    bool search(int A[], int n, int target) {
		int left = 0;
		int right = n-1;
		while(left <= right){
			int mid = (left + right)/2;
			if(target == A[mid])
				return true;
			else if(A[left] < A[mid]) {
				if(target<A[mid] && A[left]<=target)
					right = mid-1;
				else
					left = mid+1;
			} else if(A[left] > A[mid]) {
				if(target>A[mid] && A[right]>=target)
					left = mid+1;
				else
					right = mid-1;
			} else
				++left;
		}
		
		return false;
    }
};



































class Solution {
public:
    bool search(int A[], int n, int target);
};

bool Solution::search(int A[], int n, int target)
{
	int l = 0;
	int r = n-1;
	while(l <= r)
	{
		int m = (l + r) / 2;
		if(target == A[m])
			return true;
			//return m;
		
		// compare A[m], A[l] and A[r]
		if(A[m] > A[l]) // A[l...m] are sorted
		{
			if(target<A[m] && target>=A[l])
				r = m - 1;
			else
				l = m + 1;
		}
		else if(A[m] < A[l]) // the right side are sorted
		{
			if(target>A[m] && target<=A[r])
				l = m + 1;
			else
				r = m - 1;
		}
		else //skip duplicate one, A[l] == A[mid]
			++l;
	}
	
	return false;
}
