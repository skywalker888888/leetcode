/**
		Given two sorted integer arrays A and B, merge B into A as one sorted array.
		Note:
		You may assume that A has enough space to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.
*/
// pass 3
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
		for(int i=m-1; i>=0; --i)
			A[i+n] = A[i];
		int i = n;
		int j = 0;
		int k = 0;
		while(i<m+n && j<n) 
			if(A[i] <= B[j]) {
				A[k++] = A[i++];
			} else {
				A[k++] = B[j++];
			}
		
		while(j < n)
			A[k++] = B[j++];
    }
};












































// pass 2
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
		if(!n)
			return;
		else if(!m)
			for(int i=0; i<n; ++i)
				A[i] = B[i];
		else{
			int lastIndex = m + n -1;
			int indexA = m - 1;
			int indexB = n - 1;
			while(indexB>=0 && indexA>=0){
				if(A[indexA] > B[indexB]){
					A[lastIndex] = A[indexA];
					--lastIndex;
					--indexA;
				}else{
					A[lastIndex] = B[indexB];
					--lastIndex;
					--indexB;
				}
			}
			
			// 
			while(indexB >= 0){
				A[lastIndex] = B[indexB];
				--lastIndex;
				--indexB;
			}
		}
    }
};


























class Solution
{
public:
    void merge(int A[], int m, int B[], int n);
};


void Solution::merge(int A[], int m, int B[], int n)
{
	// move A's items right
	for(int i=m-1; i>=0; --i)
		A[i+n] = A[i];
		
	// merge
	int indexA = n;
	int indexB = 0;
	int i;
	for(i=0; i<m+n && indexB<n; ++i)
		if(indexA<m+n && A[indexA]<=B[indexB])
		{
			A[i] = A[indexA];
			++indexA;
		}
		else
		{
			A[i] = B[indexB];
			++indexB;
		}
}
