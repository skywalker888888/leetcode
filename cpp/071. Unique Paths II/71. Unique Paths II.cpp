/**
		Follow up for "Unique Paths":

		Now consider if some obstacles are added to the grids. How many unique paths would there be?

		An obstacle and empty space is marked as 1 and 0 respectively in the grid.

		For example,
		There is one obstacle in the middle of a 3x3 grid as illustrated below.

		[
		  [0,0,0],
		  [0,1,0],
		  [0,0,0]
		]
		The total number of unique paths is 2.

		Note: m and n will be at most 100.
		
		See also: 72. Unique Paths
*/
// pass 3
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
		int m = obstacleGrid.size();
		if(!m)
			return 0;
		int n = obstacleGrid[0].size();
		if(!n)
			return 0;
		
		vector<vector<int> > M(2, vector<int>(n, 0));
		for(int i=0; i<n; ++i) 
			if(obstacleGrid[0][i] == 1)
				M[0][i] = 0;
			else if(i == 0)
				M[0][i] = 1;
			else
				M[0][i] = M[0][i-1];
				
		int flag = 1;
		for(int i=1; i<m; ++i) {
			if(obstacleGrid[i][0] == 1)
				M[flag][0] = 0;
			else
				M[flag][0] = M[!flag][0];
			for(int j=1; j<n; ++j) {
				if(obstacleGrid[i][j] == 1)
					M[flag][j] = 0;
				else
					M[flag][j] = M[flag][j-1] + M[!flag][j];
			}
			flag = !flag;
		}
		return M[!flag][n-1];
    }
};




































// pass 2
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
		int m = obstacleGrid.size();
		if(!m)
			return 0;
		int n = obstacleGrid[0].size();
		if(!n)
			return 0;
		
		vector<vector<int> > paths(2, vector<int>(n, 0));
		int cnt = 1;
		for(int i=0; i<n; ++i) {
			if(obstacleGrid[0][i] == 1)
				cnt = 0;
			paths[0][i] = cnt;
		}

		int flag = 1;
		for(int i=1; i<m; ++i) {
			for(int j=0; j<n; ++j) {
				if(obstacleGrid[i][j] == 1)
					paths[flag][j] = 0;
				else if(!j)
					paths[flag][j] = paths[!flag][j];
				else
					paths[flag][j] = paths[flag][j-1] + paths[!flag][j];
			}
			flag = !flag;
		}
		
		return paths[!flag][n-1];
    }
};



































class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid)
	{
		int m = obstacleGrid.size();
		if(!m)
			return 0;
		int n = obstacleGrid[0].size();
		if(!n)
			return 0;
			
		vector<vector<int> > matrix(m, vector<int>(n, 0));
		
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(obstacleGrid[i][j])
					matrix[i][j] = 0;
				else if(!i && !j)
					if(obstacleGrid[i][j])
						return 0;
					else
						matrix[i][j] = 1;
				else if(!i)
					if(obstacleGrid[i][j-1])
						matrix[i][j] = 0;
					else
						matrix[i][j] = matrix[i][j-1];
				else if(!j)
					if(obstacleGrid[i-1][j])
						matrix[i][j] = 0;
					else
						matrix[i][j] = matrix[i-1][j];
				else
						matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
		
		return matrix[m-1][n-1];
	}
};




