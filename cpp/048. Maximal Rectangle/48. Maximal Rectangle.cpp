/**
		Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
		
		See also: 49. Largest Rectangle in Histogram
*/
// pass 3
class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
		int m = matrix.size();
		if(!m)
			return 0;
		int n = matrix[0].size();
		if(!n)
			return 0;
		
		vector<int> height(n, 0);
		int nmax = 0;
		for(int i=0; i<m; ++i) {
			for(int j=0; j<n; ++j)
				if(matrix[i][j] == '0')
					height[j] = 0;
				else
					++height[j];
			
			// 
			nmax = max(nmax, maximalRectangle(height));
		}
		return nmax;
    }
	
	int maximalRectangle(vector<int> height) {
		int n = height.size();
		
		vector<int> left(n, 0);
		vector<int> right(n, 0);
		
		stack<int> stkLeft;
		for(int i=0; i<n; ++i) {
			while(!stkLeft.empty() && height[stkLeft.top()]>=height[i])
				stkLeft.pop();
			left[i] = stkLeft.empty()?0:stkLeft.top()+1;
			stkLeft.push(i);
		}
		
		stack<int> stkRight;
		for(int i=n-1; i>=0; --i) {
			while(!stkRight.empty() && height[stkRight.top()]>=height[i])
				stkRight.pop();
			right[i] = stkRight.empty()?n-1:stkRight.top()-1;
			stkRight.push(i);
		}
		int nmax = 0;
		for(int i=0; i<n; ++i) 
			nmax = max(nmax, height[i] * (right[i]-left[i]+1));
		return nmax;
	}
};

















































// pass 2
class Solution {
public:
	// Time: O(n^2)
	// Space: O(n^2)
    int maximalRectangle(vector<vector<char> > &matrix) {
		int m = matrix.size();
		if(!m)
			return 0;
		int n = matrix[0].size();
		if(!n)
			return 0;
		
		// m*n matrix
		vector<vector<int> > M(m, vector<int>(n, 0));
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(matrix[i][j] == '1')
					M[i][j] = (!i)?1:M[i-1][j]+1;
				else
					M[i][j] = 0;
		
		int maxarea = -1;
		for(int i=0; i<m; ++i)
			maxarea = max(maxarea, calculateMaxArea(M[i]));
		return maxarea;
    }
	
	// O(n)
	int calculateMaxArea(const vector<int> &heights){
		int n = heights.size();
		
		// for each item i, calculate the number of left items, not including the item i itself, which is bigger than item i.
		vector<int> vtrLeft(n, 0);
		stack<int> stkLeft;
		for(int i=0; i<n; ++i){
			while(!stkLeft.empty() && heights[stkLeft.top()]>=heights[i])
				stkLeft.pop();
			vtrLeft[i] = (!stkLeft.empty())?(i-stkLeft.top()-1):i;
			stkLeft.push(i);
		}
		
		// right side
		vector<int> vtrRight(n, 0);
		stack<int> stkRight;
		for(int i=n-1; i>=0; --i){
			while(!stkRight.empty() && heights[stkRight.top()]>=heights[i])
				stkRight.pop();
			vtrRight[i] = (!stkRight.empty())?(stkRight.top()-i-1):(n-i-1);
			stkRight.push(i);
		}
		
		int maxArea = (vtrRight[0]+vtrLeft[0]+1)*heights[0];
		for(int i=1; i<n; ++i)
			maxArea = max(maxArea, (vtrRight[i]+vtrLeft[i]+1)*heights[i]);
		return maxArea;
	}
};





















































class Solution
{
public:
    int maximalRectangle(vector<vector<char> > &matrix);
private:
	int calculateMaxHistogramArea(vector<int>& M);
	pair<int, int> makePair(int i, int j);
};


pair<int, int> Solution::makePair(int i, int j)
{
	pair<int, int> pos;
	pos.first = i;
	pos.second = j;
	return pos;
}


/**
	User Dynamic programming. 
	http://stackoverflow.com/questions/4311694/maximize-the-rectangular-area-under-histogram
	http://stackoverflow.com/questions/2478447/find-largest-rectangle-containing-only-zeros-in-an-nn-binary-matrix
*/
int Solution::maximalRectangle(vector<vector<char> > &matrix)
{
	int m = matrix.size();
	if(!m)
		return 0;
	int n = matrix[0].size();
	if(!n)
		return 0;
	// create a matrix M[i][j] where M[i] is the hight of line i. 
	vector<vector<int> > M(m, vector<int>(n, 0));
		
	// calculate the height for each column
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(matrix[i][j] == '1')
				if(!i)
					M[i][j] = 1;
				else
					M[i][j] = M[i-1][j] + 1;
			else
				M[i][j] = 0;
			
	int nMax = 0;
	for(int i=0; i<m; ++i)
		nMax = max(nMax, calculateMaxHistogramArea(M[i]));
	return nMax;
}

int Solution::calculateMaxHistogramArea(vector<int>& M)
{
	int n = M.size();
	
	if(!n)
		return 0;
	
	// left side
	vector<int> vtrLeft(n, 0);
	stack<int> stkLeft;
	for(int i=0; i<n; ++i)
	{
		while(!stkLeft.empty() && M[i]<=M[stkLeft.top()])
			stkLeft.pop();
		if(stkLeft.empty())
			vtrLeft[i] = i;
		else
		{
			int nLInd = stkLeft.top();
			vtrLeft[i] = i-nLInd-1; // not including the item i
		}
		stkLeft.push(i);
	}
	
	// right side
	vector<int> vtrRight(n, 0);
	stack<int> stkRight;
	for(int i=n-1; i>=0; --i)
	{
		while(!stkRight.empty() && M[i]<=M[stkRight.top()])
			stkRight.pop();
		if(stkRight.empty())
			vtrRight[i] = n-1-i;
		else
			vtrRight[i] = stkRight.top()-i-1;
		stkRight.push(i);
	}
	
	//
	int nMax = 0;
	for(int i=0; i<n; ++i)
		nMax = max(nMax, M[i] * (vtrLeft[i]+vtrRight[i]+1));
	
	return nMax;
}



