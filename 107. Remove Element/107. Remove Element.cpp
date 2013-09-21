/**
		Given an array and a value, remove all instances of that value in place and return the new length.
		The order of elements can be changed. It doesn't matter what you leave beyond the new length.
*/
// pass 3
class Solution {
public:
    int removeElement(int A[], int n, int elem) {
		int i = -1;
		for(int j=0; j<n; ++j) 
			if(A[j] != elem)
				A[++i] = A[j];
		return i+1;
    }
};
















































// pass 2
class Solution {
public:
    int removeElement(int A[], int n, int elem) {
		int i = -1;
		int j = 0;
		int len = n;
		while(j < n) {
			if(A[j] != elem) {
				A[i+1] = A[j];
				++i;
			}
			else 
				--len;
			++j;
		}
		
		return len;
    }
};












































class Solution {
public:
	int removeElement(int A[], int n, int elem)
	{
		int len = n;
		for(int i=0; i<len;) {
			if(A[i] == elem) {
				swap(A[i], A[len-1]);
				--len;
			}
			else
				++i;
		}
		
		return len;
	}
};




