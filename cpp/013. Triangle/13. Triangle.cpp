#include <vector>
#include <iostream>
#include <limits>
using namespace std;

/**
		Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

		For example, given the following triangle
		[
			 [2],
			[3,4],
		   [6,5,7],
		  [4,1,8,3]
		]
		The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

		Note:
		Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.	
*/
// pass 3
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
    	int n = triangle.size();
		if(!n)
			return 0;
		vector<vector<int> > minValues(2, vector<int>(n, 0));
		minValues[0][0] = triangle[0][0];
		int flag = 1;
		for(int i=1; i<n; ++i) {
			for(int j=0; j<=i; ++j) {
				if(!j)
					minValues[flag][j] = triangle[i][0] + minValues[!flag][j];
				else if(j == i) 
					minValues[flag][j] = triangle[i][j] + minValues[!flag][j-1];
				else
					minValues[flag][j] = triangle[i][j] + min(minValues[!flag][j-1], minValues[!flag][j]);
			}
			flag = !flag;
		}
		
		int result = minValues[!flag][0];
		for(int i=0; i<n; ++i)
			result = min(result, minValues[!flag][i]);
		return result;
    }
};




























// Pass 2
/*
		Solution:
			1. Use DP to calculate M[i,j]
			2. We can use two n-size array to do the calculation. Because we can alwasy generate the values for line i from line i-1, shown as in minimumTotal3, we can to it in a loop.
*/
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle);
};


int Solution::minimumTotal(vector<vector<int> > &triangle)
{
	int nrow = triangle.size();
	if(!nrow)
		return 0;
	
	// (i, j) can be reached from (i-1, j-1) and (i-1, j)
	vector<vector<int> >tot(2, vector<int>(nrow, 0));
	tot[0][0] = triangle[0][0];
	int flag = 1;
	for(int i=1; i<nrow; ++i)
	{
		for(int j=0; j<=i; ++j)
		{
			// calculate (i,j)
			//int i1 = i-1;
			int j1 = j-1;
			if(j1>=0 && j<=i-1)
				tot[flag][j] = min(tot[!flag][j-1], tot[!flag][j]) + triangle[i][j];
			else if(j1<0)
				tot[flag][j] = tot[!flag][j] + triangle[i][j];
			else if(j==i)
				tot[flag][j] = tot[!flag][j1] + triangle[i][j];
		}
		
		flag = !flag;
	}
	
	int minval = tot[!flag][0];
	for(int i=0; i<nrow; ++i)
		if(minval > tot[!flag][i])
			minval = tot[!flag][i];
			
	return minval;
}

int main(int argc, char **argv)
{
	vector<vector<int> > triangle;
	int n = 4;
	triangle.resize(n);
	for(int i=0; i<n; i++)
	{
		triangle[i].resize(n);
	}

	// [[-1],[2,3],[1,-1,-3]]
	triangle[0][0] = 2;
	triangle[1][0] = 3;
	triangle[1][1] = 4;
	triangle[2][0] = 5;
	triangle[2][1] = 6;
	triangle[2][2] = 7;
	triangle[3][0] = 3;
	triangle[3][1] = 4;
	triangle[3][2] = 1;
	triangle[3][3] = 8;
	
	
	Solution solu;
	int num = solu.minimumTotal(triangle);
	cout << " " << num << "\n";
}






















class Solution
{
	static const int MAXINFI;
	static const int MININFI;
public:
    int minimumTotal(vector<vector<int> > &triangle);
    int minimumTotal3(vector<vector<int> > &triangle);
    int minimumTotal2(vector<vector<int> > &triangle);
	
private:
	void calculateMatrix(int i, int j, vector<vector<int> > &triangle, vector<vector<int> > &matrix);
};

const int Solution::MAXINFI = numeric_limits<int>::max();
const int Solution::MININFI = numeric_limits<int>::min();

int Solution::minimumTotal(vector<vector<int> > &triangle)
{
	int n = triangle.size();
	if(!n)
		return 0;
		
	vector<int> lastMinLine;
	vector<int> curMinLine;
	lastMinLine.resize(n);
	curMinLine.resize(n);
	
	lastMinLine[0] = triangle[0][0];
	curMinLine[0] = triangle[0][0];
	for(int i=1; i<n; i++)
	{
		for(int j=0; j<=i; j++)
		{
			// calculate curMinLine[i][j]
			int nMinSum = MAXINFI;
			if(j-1 >= 0)
				nMinSum = min(nMinSum, lastMinLine[j-1]+triangle[i][j]);
			if(j <= i-1)
				nMinSum = min(nMinSum, lastMinLine[j]+triangle[i][j]);
			curMinLine[j] = nMinSum;
		}
		
		lastMinLine = curMinLine;
	}
	int nMin = MAXINFI;
	for(int i=0; i<n; i++)
		nMin = min(nMin, curMinLine[i]);
	return nMin;
}


int Solution::minimumTotal3(vector<vector<int> > &triangle)
{
	int n = triangle.size();
	vector<vector<int> > matrix;
	matrix.resize(n);
	for(int i=0; i<n; i++)
	{
		matrix[i].resize(n);
		// triangle
		for(int j=0; j<=n; j++)
			matrix[i][j] = MAXINFI;
	}
	matrix[0][0] = triangle[0][0];
	
	for(int i=0; i<n; i++)
		for(int j=0; j<=i; j++)
		{
			if(!i)
				matrix[i][j] = triangle[i][j];
			else
			{
				// calculate from i-1 line
				int nMin = MAXINFI;
				if(j-1 >= 0)
					nMin = min(nMin, matrix[i-1][j-1] + triangle[i][j]);
				if(j <= i)
					nMin = min(nMin, matrix[i-1][j] + triangle[i][j]);
				matrix[i][j] = nMin;
			}
		}
	
}

int Solution::minimumTotal2(vector<vector<int> > &triangle)
{
	int n = triangle.size();
	vector<vector<int> > matrix;
	matrix.resize(n);
	for(int i=0; i<n; i++)
	{
		matrix[i].resize(n);
		// triangle
		for(int j=0; j<=n; j++)
			matrix[i][j] = MAXINFI;
	}
	matrix[0][0] = triangle[0][0];
	
	int nMin = MAXINFI;
	for(int i=0; i<n; i++)
	{
		calculateMatrix(n-1, i, triangle, matrix);
		nMin = min(nMin, matrix[n-1][i]);
	}
	
	return nMin;
}

void Solution::calculateMatrix(int i, int j, vector<vector<int> > &triangle, vector<vector<int> > &matrix)
{
	if(matrix[i][j] < MAXINFI)
		return;
	else if(!i)
	{
		if(j<=i)
			matrix[i][j] = triangle[i][j];
	}
	else
	{
		// i>0
		if(j > i)
			return;
		
		int nMin = MAXINFI;
		// j <= i
		if(j-1 >= 0)
		{
			calculateMatrix(i-1, j-1, triangle, matrix);
			//nMin = min(nMin, matrix[i-1][j-1]+triangle[i][j]);
			int nNum = matrix[i-1][j-1]+triangle[i][j];
			if(nMin > nNum)
				nMin = nNum;
		}
		if(j <= i-1)
		{
			calculateMatrix(i-1, j, triangle, matrix);
			//nMin = min(nMin, matrix[i-1][j]+triangle[i][j]);
			int nNum = matrix[i-1][j]+triangle[i][j];
			if(nMin > nNum)
				nMin = nNum;
		}
		matrix[i][j] = nMin;
	}
}


int main(int argc, char **argv)
{
	vector<vector<int> > triangle;
	int n = 3;
	triangle.resize(n);
	for(int i=0; i<n; i++)
	{
		triangle[i].resize(n);
	}

	// [[-1],[2,3],[1,-1,-3]]
	triangle[0][0] = -1;
	triangle[1][0] = 2;
	triangle[1][1] = 3;
	triangle[2][0] = 1;
	triangle[2][1] = -1;
	triangle[2][2] = -3;
	
	
	Solution solu;
	int num = solu.minimumTotal(triangle);
	cout << " " << num << "\n";
}


