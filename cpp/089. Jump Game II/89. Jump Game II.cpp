#include <vector>
using namespace std;

/**
		Given an array of non-negative integers, you are initially positioned at the first index of the array.

		Each element in the array represents your maximum jump length at that position.

		Your goal is to reach the last index in the minimum number of jumps.

		For example:
		Given array A = [2,3,1,1,4]

		The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
		
	See 79. Jump Game
		
*/
// pass 3
class Solution {
public:
    int jump(int A[], int n) {
		int result = 0;
		int i = 0;
		while(i < n-1) {
			++result;
			if(i+A[i] >= n-1)
				return result;
			int k = i+1;
			for(int j=i+1; j<=i+A[i]; ++j) 
				if(j+A[j] > k+A[k])
					k = j;
			if(k+A[k] >= i+A[i])
				i = k;
		}
		
		return result;
    }
};



































// pass 2
class Solution {
public:
    int jump(int A[], int n) {
		if(n < 2)
			return 0;
		int ind = 0;
		int result = 0;
		
		while(ind < n) {
			if(ind >= n-1)
				return result;
			else if(ind+A[ind] >= n-1)
				return result + 1;
			
			// pick the position to jump to
			int nextInd = ind+1;
			int maxPos = nextInd + A[nextInd];
			for(int i=nextInd; i<=ind+A[ind]; ++i)
				if(maxPos < i+A[i]) {
					maxPos = i+A[i];
					nextInd = i;
				}
			
			ind = nextInd;
			++result;
		}
		
		return result;
    }
};


































class Solution {
public:
    int jump(int A[], int n);
    int jump4(int A[], int n);
    int jump3(int A[], int n);
    int jump2(int A[], int n);
};


class Solution {
public:
	/**
		Greedy algorithm:
			we will always jump to the position which can jump to a furthest position.
			This is the optimal choice, because next time we have better choice 
	 */
	int jump(int A[], int n)
	{
		if(n < 2)
			return 0;
		
		int start = 0;
		int nsteps = 0;
		while(start < n) {
			if(A[start] <= 0)
				return -1;
			++nsteps;
			int curMax = start + A[start];
			if(curMax >= n-1)
				return nsteps;
			int nmax = 0;
			for(int j=start+1; j<=curMax; ++j)
				if(j + A[j] >= nmax) {
					nmax = j + A[j];
					start = j;
				}
		}
		
		return -1;
	}
};

class Solution {
public:
	int jump(int A[], int n)
	{
		if(n < 2)
			return 0;
		
		vector<vector<int> > matrix(n, vector<int>(n, -1));
		for(int nLen = 1; nLen<n; ++nLen)
			for(int i=0; i<n-nLen; ++i) {
				int j = i + nLen;
				
				if(A[i] >= nLen)
					matrix[i][j] = 1;
				else {
					// (i,j)
					int nMin = -1;
					bool bHasMinValue = false;
					for(int k=i+1; k<j; ++k)
						if(matrix[i][k]>0 && matrix[k][j]>0) {
							int nsteps = matrix[i][k] + matrix[k][j];
							if(!bHasMinValue)
								nMin = nsteps;
							else if(nMin > nsteps)
								nMin = nsteps;
							bHasMinValue = true;
						}
					matrix[i][j] = nMin;
				}
			}
		return matrix[0][n-1];
	}
};

class Solution {
public:
	int jump(int A[], int n) {
		if(n < 2)
			return 0;

		vector<bool> visited(n, false);
		
		// do BFS
		int nSteps = 0;
		queue<int> firstQ, *pfirst;
		queue<int> secondQ, *psecond;
		firstQ.push(0);
		visited[0] = true;
		pfirst = &firstQ;
		psecond = &secondQ;
		while(!pfirst->empty()) {
			++nSteps;
			while(!pfirst->empty()) {
				int nodenum = pfirst->front();
				pfirst->pop();
				for(int i=1; i<=A[nodenum] && nodenum+i<n; ++i) {
					int child = nodenum+i;
					if(child == n-1)
						return nSteps;
					if(!visited[child]) {
						visited[child] = true;
						psecond->push(child); 
					}
				}
			}
			swap(pfirst, psecond);
		}
		return -1;
	}
};


class Solution {
public:
	int jump(int A[], int n) {

		if(n<2)
			return 0;
			
		int nmin;
		bool bHasMin = false;
		
		vector<int> steps(n, -1);
		steps[0] = 0;
		for(int i=0; i<n; ++i)
		{
			if(steps[i]>=0)
				for(int j=i+1; j<=i+A[i] && j<n; ++j)
				{
					if(steps[j]<0 || 1+steps[i]<steps[j])
						steps[j] = 1+steps[i];
						
					if(j == n-1)
					{
						if(!bHasMin || nmin < steps[j])
							nmin = steps[j];
							bHasMin = true;
					}
				}
		}
		
		if(!bHasMin)
			return -1;
		return nmin;
	}
};

