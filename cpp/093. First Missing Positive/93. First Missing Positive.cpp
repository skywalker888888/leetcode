/**
		Given an unsorted integer array, find the first missing positive integer.

		For example,
		Given [1,2,0] return 3,
		and [3,4,-1,1] return 2.

		Your algorithm should run in O(n) time and uses constant space.
		
*/
// pass 3
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
		for(int i=0; i<n; ) {
			int k = A[i];
			if(k==i+1 || k>n || k<=0 || A[k-1]==k)
				++i;
			else {
				int k = A[i];
				swap(A[i], A[k-1]);
			}
		}
		int mis = 0;
		for(int i=0; i<n; ++i) {
			if(A[i] != i+1)
				return i+1;
			mis = i+1;
		}
		return n+1;
    }
};







































/*
		http://stackoverflow.com/questions/1586858/find-the-smallest-integer-not-in-a-list
		An interesting interview question that a colleague of mine uses:
		Suppose that you are given a very long, unsorted list of unsigned 64-bit integers. How would you find the smallest non-negative integer that does not occur in the list?
		FOLLOW-UP: Now that the obvious solution by sorting has been proposed, can you do it faster than O(n log n)?
		FOLLOW-UP: Your algorithm has to run on a computer with, say, 1GB of memory
		CLARIFICATION: The list is in RAM, though it might consume a large amount of it. You are given the size of the list, say N, in advance.
*/
// pass 2
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
		int i = 0;
		while(i < n) {
			if(A[i] == i+1)
				++i;
			else {
				if(A[i]>0 && A[i]<=n) {
					if(A[A[i]-1] == A[i])
						++i; // skip this number
					else {
						swap(A[A[i]-1], A[i]);
					}
				} else 
					++i;
			}
		}
		i = 0;
		while(i < n) {
			if(A[i] != i+1)
				return i+1;
			++i;
		}
		
		return n+1;
    }
};



































class Solution {
public:
	/**
		If the datastructure can be mutated in place and supports random access then you can do it in O(N) time and O(1) additional space. Just go through the array sequentially and for every index write the value at the index to the index specified by value, recursively placing any value at that location to its place and throwing away values > N. Then go again through the array looking for the spot where value doesn't match the index - that's the smallest value not in the array. This results in at most 3N comparisons and only uses a few values worth of temporary space.
	*/
	int firstMissingPositive(int A[], int n)
	{
		if(!n)
			return 1;
		if(n==1)
			if(A[0]==1)
				return 2;
			else
				return 1;
		for(int i=0; i<n; ++i)
			// 0..n
			while(A[i]>0 && A[i]<=n && A[A[i]-1]!=A[i])
				swap(A[i], A[A[i]-1]);
		for(int i=0; i<n; ++i)
			if(A[i]!=i+1)
				return i+1;
		
		return A[n-1]+1;
	}
};




