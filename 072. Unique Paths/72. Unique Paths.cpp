/**
		A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
		The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
		How many possible unique paths are there?
		Note: m and n will be at most 100.
		
		See also: 71. Unique Paths II
*/
// pass 3
class Solution {
public:
    int uniquePaths(int m, int n) {
		if(!m || !n)
			return 0;
		vector<vector<int> > M(2, vector<int>(n, 1));
		int flag = 1;
		for(int i=1; i<m; ++i) {
			M[flag][0] = M[!flag][0];
			for(int j=1; j<n; ++j) 
				M[flag][j] = M[flag][j-1] + M[!flag][j];
			flag = !flag;
		}
		
		return M[!flag][n-1];
    }
};









































class Solution {
public:
    int uniquePaths(int m, int n) {
		if(!m)
			return 0;
		if(!n)
			return 0;
		
		vector<vector<int> > paths(2, vector<int>(n, 0));
		for(int i=0; i<n; ++i)
			paths[0][i] = 1;
		
		int flag = 1;
		for(int i=1; i<m; ++i) {
			paths[flag][0] = 1;
			for(int j=1; j<n; ++j)
				paths[flag][j] = paths[flag][j-1] + paths[!flag][j];
			flag = !flag;
		}
		
		return paths[!flag][n-1];
    }
};















































class Solution {
public:
	int uniquePaths(int m, int n)
	{
		if(!m)
			return 0;
		if(!n)
			return 0;
		
		vector<vector<int> > matrix(m, vector<int>(n, 0));
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(!i && !j)
					matrix[i][j] = 1;
				else if(!i)
					matrix[i][j] = 1;
				else if(!j)
					matrix[i][j] = 1;
				else
					matrix[i][j] = matrix[i-1][j]+matrix[i][j-1];
					
		return matrix[m-1][n-1];
	}
};


