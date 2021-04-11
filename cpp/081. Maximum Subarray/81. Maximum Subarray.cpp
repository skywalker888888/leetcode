/**
		Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

		For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
		the contiguous subarray [4,-1,2,1] has the largest sum = 6.
		
		More practice:
		If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/
// pass 3
class Solution {
public:
    int maxSubArray(int A[], int n) {
		if(!n)
			return 0;
		int result = A[0];
		int tmp = 0;
		for(int i=0; i<n; ++i) {
			tmp += A[i];
			if(tmp > result)
				result = tmp;
			if(tmp < 0)
				tmp = 0;
		}
		
		return result;
    }
};











































// pass 2
class Solution {
public:
    int maxSubArray(int A[], int n) {
		if(!n)
			return 0;
		int maxSum = A[0];
		int maxIndexLeft = 0;
		int maxIndexRight = 0;
		
		int indexLeft = -1;
		int tmpSum = 0;
		for(int i=0; i<n; ++i) {
			if(indexLeft < 0)
				indexLeft  = i;
			tmpSum += A[i];
			if(tmpSum > maxSum) {
				maxIndexLeft = indexLeft;
				maxIndexRight = i;
				maxSum = tmpSum;
			}
			
			if(tmpSum < 0) {
				indexLeft = i+1;
				tmpSum = 0;
			}
		}
		
		return maxSum;
    }
};










































class Solution {
public:
	int maxSubArray(int A[], int n)
	{
		if(!n)
			return 0;

		int nMax = A[0];

		int nLocMax = 0;
		for(int i=0; i<n; ++i) {
			nLocMax += A[i];
			if(nMax < nLocMax)
				nMax = nLocMax;
			if(nLocMax < 0)
				nLocMax = 0;
		}
		
		return nMax;
	}
};

class Solution {
public:
	int maxSubArray1(int A[], int n)
	{
		int nMax = A[0];
		for(int i=0; i<n; ++i) {
			// length
			int nInitVal = 0;
			for(int nLen=0; nLen<n-i; ++nLen) {
				int j = i + nLen;
				nInitVal += A[j];
				if(nInitVal > nMax)
					nMax = nInitVal;
			}
		}
		
		return nMax;
	}
};


class Solution {
public:
	int maxSubArray(int A[], int n) {
		if(!n)
			return 0;
		
		return maxSubArray(A, n, 0, n-1);
	}
	int maxSubArray(int A[], int n, int i, int j) {
		if(i == j)
			return A[i];
		else if(i+1 == j) {
			int nMax1 = A[i];
			int nMax2 = A[j];
			int nMax3 = A[i] + A[j];
			
			int nMax = nMax1;
			nMax = max(nMax, nMax2);
			nMax = max(nMax, nMax3);
			return nMax;
		}
		
		int mid = (i+j)/2;
		int max1 = maxSubArray(A, n, i, mid);
		int max2 = maxSubArray(A, n, mid, j);
		
		// calculate the max subarray which pass the mid position
		int max3 = A[mid];
		int nmax0 = max3;
		for(int j=mid; j-1>=0; --j) {
			max3 += A[j-1];
			if(nmax0 < max3)
				nmax0 = max3;
		}
		for(int j=mid; j+1<n; ++j) {
			max3 = max3+A[j+1];
			if(nmax0 < max3)
				nmax0 = max3;
		}
		max3 = nmax0;
			
		int nmax = max1;
		nmax = max(nmax, max2);
		nmax = max(nmax, max3);
		
		return nmax;
	}
};




