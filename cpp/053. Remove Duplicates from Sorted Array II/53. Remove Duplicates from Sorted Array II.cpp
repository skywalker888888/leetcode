/**
		Follow up for "Remove Duplicates":
		What if duplicates are allowed at most twice?

		For example,
		Given sorted array A = [1,1,1,2,2,3],

		Your function should return length = 5, and A is now [1,1,2,2,3].
		
		See also: 108. Remove Duplicates from Sorted Array
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
			if(A[i] == A[j]) {
				if(i>0 && A[i-1]==A[i]) {
					++j;
				} else {
					A[i+1] = A[j];
					++i;
					++j;
				}
			} else {
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
		if(!n)
			return 0;
		int j = 0;
		for(int i=1; i<n;){
			if(j>0 && A[i]==A[j] && A[i]==A[j-1])
				++i;
			else
				A[++j] = A[i++];
		}
		
		return j+1;
    }
};







































class Solution {
public:
    int removeDuplicates(int A[], int n);
};



int Solution::removeDuplicates(int A[], int n)
{
	int index = 0;
	int nPre = -1;
	int nPPre = -1;
	
	while(index < n)
	{
		// 
		int i = index + 1;
		while(i<n && A[i]==A[index])
			++i;
	
		// delete the necessary duplicates
		// 
		if(i - index > 2)
		{
			int nSize = n - (i-index-2);
			int k = index + 2;
			for(int k=index + 2; i<n;)
				A[k++] = A[i++];
			n = nSize;
			index += 2;
		}
		else
			index = i;
	}
	return n;
}


