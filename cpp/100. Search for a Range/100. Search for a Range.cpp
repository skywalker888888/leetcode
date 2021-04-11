/**
		Given a sorted array of integers, find the starting and ending position of a given target value.

		Your algorithm's runtime complexity must be in the order of O(log n).

		If the target is not found in the array, return [-1, -1].

		For example,
		Given [5, 7, 7, 8, 8, 10] and target value 8,
		return [3, 4].
*/
// pass 3
class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
		int s = 0;
		int e = n-1;
		int start = n;
		while(s <= e) {
			int m = (s+e)/2;
			if(target == A[m]) {
				start = min(start, m);
				e = m - 1;
			} else if(target > A[m])
				s = m+1;
			else 
				e = m - 1;
		}
		
		s = 0;
		e = n-1;
		int end = -1;
		while(s <= e) {
			int m = (s+e)/2;
			if(target == A[m]) {
				end = max(end, m);
				s = m + 1;
			} else if(target > A[m])
				s = m + 1;
			else
				e = m - 1;
		}
		vector<int> result;
		if(start == n) {
			start = -1;
			end = -1;
		}
		result.push_back(start);
		result.push_back(end);
		return result;
    }
};


























// pass 2
class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
		int l = -1;
		int r = -1;
		// left
		int s = 0;
		int e = n-1;
		while(s <= e) {
			int m = (s + e)/2;
			if(target == A[m]) {
				l = m;
				e = m-1;
			}
			else if(target > A[m])
				s = m + 1;
			else 
				e = m - 1;
		}
		
		// right
		s = 0;
		e = n-1;
		while(s <= e) {
			int m = (s+e)/2;
			if(target == A[m]) {
				r = m;
				s = m + 1;
			}
			else if(target > A[m])
				s = m + 1;
			else 
				e = m - 1;
		}
		
		vector<int> result;
		result.push_back(l);
		result.push_back(r);
		return result;
    }
};











































class Solution {
public:
	vector<int> searchRange(int A[], int n, int target)
	{
		int l = -1;
		int r = -1;
		
		vector<int> result;
		// find the left position
		int s = 0;
		int e = n-1;
		while(s <= e) {
			int m = (s+e)/2;
			if(target == A[m]) {
				l = m;
				e = m-1;
			}
			else if(target > A[m])
				s = m + 1;
			else 
				e = m - 1;
		}
		
		// find the right position
		s = 0;
		e = n-1;
		while(s <= e) {
			int m = (s+e)/2;
			if(target == A[m]) {
				r = m;
				s = m+1;
			}
			else if(target > A[m])
				s = m + 1;
			else 
				e = m - 1;
		}
		
		result.push_back(l);
		result.push_back(r);
		
		return result;
	}
};




