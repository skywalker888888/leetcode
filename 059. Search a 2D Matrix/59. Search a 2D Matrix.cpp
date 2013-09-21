/**
		Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

		Integers in each row are sorted from left to right.
		The first integer of each row is greater than the last integer of the previous row.
		For example,

		Consider the following matrix:

		[
		  [1,   3,  5,  7],
		  [10, 11, 16, 20],
		  [23, 30, 34, 50]
		]
		Given target = 3, return true.
*/
// pass 2
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
    	int m = matrix.size();
		if(!m)
			return false;
		int n = matrix[0].size();
		if(!n)
			return false;
		int s = 0;
		int e = m*n - 1;
		while(s <= e) {
			int p = (s+e)/2;
			int i = p/n;
			int j = p%n;
			if(matrix[i][j] == target)
				return true;
			else if(target > matrix[i][j])
				s = p + 1;
			else
				e = p - 1;
		}
		return false;
    }
};




































// pass2
// Time: O(logm + logn)
// Space: O(1)
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
    	int m = matrix.size();
		if(!m)
			return false;
		int n = matrix[0].size();
		if(!n)
			return false;
		
		// search 0..m*n-1
		int left = 0;
		int right = m*n - 1;
		while(left <= right) {
			int mid = (left+right)/2;
			int i = mid/n;
			int j = mid%n;
			int val = matrix[i][j];
			if(target == val)
				return true;
			else if(target < val)
				right = mid - 1;
			else
				left = mid + 1;
		}
		
		return false;
    }
};





































class Solution {
public:
	// O(n)
	bool searchMatrix(vector<vector<int> > &matrix, int target)
	{
		int m = matrix.size();
		if(!m)
			return false;
		int n = matrix[0].size();
		if(!n)
			return false;
			
		bool bExists = searchMatrix(matrix, 0, 0, m-1, n-1, target);
		return bExists;
	}


	bool searchMatrix(vector<vector<int> > &matrix, int i, int j, int m, int n, int target)
	{
		if(i > m)
			return false;
		if(j > n)
			return false;
			
		int x = (i + m)/2;
		int y = (j + n)/2;
		
		int elm = matrix[x][y];
		if( target == elm )
			return true;
			
		if(target < elm){
			bool b1 = searchMatrix(matrix, i, j, x-1, n, target);
			if(b1)
				return true;
			bool b2 = searchMatrix(matrix, i, j, m, y-1, target);
			if(b2)
				return true;
		} else {
			bool b1 = searchMatrix(matrix, x+1, j, m, n, target);
			if(b1)
				return true;
			bool b2 = searchMatrix(matrix, x, j+1, m, n, target);
			if(b2)
				return true;
		}
	}
};

