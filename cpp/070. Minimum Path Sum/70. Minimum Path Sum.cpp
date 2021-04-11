/**
		Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.
		Note: You can only move either down or right at any point in time.
*/
// pass 3
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
		int m = grid.size();
		if(!m)
			return 0;
		int n = grid[0].size();
		if(!n)
			return 0;
		
		vector<vector<int> > M(2, vector<int>(n, 0));
		for(int i=0; i<n; ++i)
			M[0][i] = grid[0][i] + ((i>0)?M[0][i-1]:0);
		int flag = 1;
		for(int i=1; i<m; ++i) {
			M[flag][0] = M[!flag][0] + grid[i][0];
			for(int j=1; j<n; ++j) {
				M[flag][j] = min(M[flag][j-1], M[!flag][j]) + grid[i][j];
			}
			flag = !flag;
		}
		return M[!flag][n-1];
    }
};














































// pass 2
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
		int m = grid.size();
		if(!m)
			return 0;
		int n = grid[0].size();
		if(!n)
			return 0;
		
		vector<vector<int> > values(2, vector<int>(n, 0));
		for(int i=0; i<n; ++i)
			if(!i)
				values[0][i] = grid[0][i];
			else
				values[0][i] = values[0][i-1] + grid[0][i];
		
		int flag = 1;
		for(int i=1; i<m; ++i) {
			values[flag][0] = values[!flag][0] + grid[i][0];
			for(int j=1; j<n; ++j) 
				values[flag][j] = min(values[flag][j-1], values[!flag][j]) + grid[i][j];
			flag = !flag;
		}
		
		return values[!flag][n-1];
    }
};
















































class Solution {
public:
	int minPathSum(vector<vector<int> > &grid)
	{
		int m = grid.size();
		if(!m)
			return 0;
		int n = grid[0].size();
		if(!n)
			return 0;
			
		vector<vector<int> > matrix(m, vector<int>(n, 0));
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(!i && !j)
					matrix[i][j] = grid[i][j];
				else if(!i)
					matrix[i][j] = matrix[i][j-1] + grid[i][j]; 
				else if(!j)
					matrix[i][j] = matrix[i-1][j] + grid[i][j]; 
				else
					matrix[i][j] = min(matrix[i][j-1], matrix[i-1][j]) + grid[i][j];

		return matrix[m-1][n-1];
	}
};



