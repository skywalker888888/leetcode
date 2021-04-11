/**
		Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
		Do not allocate extra space for another array, you must do this in place with constant memory.
		For example,
		Given input array A = [1,1,2],
		Your function should return length = 2, and A is now [1,2].
		
		See also: 53. Remove Duplicates from Sorted Array II
*/
// pass 3
class Solution {
public:
    int removeDuplicates(int A[], int n) {
		if(!n)
			return 0;
		int i = 0;
		int j = 1;
		while(j < n) {
			if(A[j] == A[i])
				++j;
			else {
				A[i+1] = A[j];
				++i;
				++j;
			}
		}
		return i+1;
    }
};












































// pass 2
class Solution {
public:
    int removeDuplicates(int A[], int n) {
		int i = 0;
		int len = n;
		for(int j=1; j<n; ++j)
			if(A[i] == A[j])
				--len;
			else {
				A[i+1] = A[j];
				++i;
			}
		return len;
    }
};































class Solution {
public:
	int removeDuplicates(int A[], int n)
	{
		if(n < 2)
			return n;
		
		int i = 0;
		int j = 1;
		int len = n;
		
		while(j<n) {
			if(A[i] == A[j])
				--len;
			else {
				++i;
				A[i] = A[j];
			}
			++j;
		}
		return len;
	}
};



