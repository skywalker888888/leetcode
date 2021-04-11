/**
		Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
		Follow up:
		Did you use extra space?
		A straight forward solution using O(mn) space is probably a bad idea.
		A simple improvement uses O(m + n) space, but still not the best solution.
		Could you devise a constant space solution?
*/
// pass 3
class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
		int m = matrix.size();
		if(!m)
			return;
		int n = matrix[0].size();
		if(!n)
			return;
		
		int posi=-1, posj=-1;
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(matrix[i][j] == 0) {
					posi = i;
					posj = j;
					break;
				}
		if(posi < 0)
			return;
		
		// line
		for(int line=0; line<m; ++line) {
			if(line != posi) {
				if(matrix[line][posj] == 0)
					matrix[line][posj] = 1;
				else {
					matrix[line][posj] = 0;
					for(int col=0; col<n; ++col) {
						if(col!=posj && matrix[line][col]==0) {
							matrix[line][posj] = 1;
							break;
						}
					}
				}
			}
		}
		
		// column
		for(int col=0; col<n; ++col) {
			if(col != posj) {
				if(!matrix[posi][col]) {
					matrix[posi][col] = 1;
				} else {
					matrix[posi][col] = 0;
					for(int line=0; line<m; ++line)
						if(line!=posi && matrix[line][col] == 0) {
							matrix[posi][col] = 1;
							break;
						}
				}
			}
		}
		
		// clear data
		// line
		for(int line=0; line<m; ++line) {
			if(line!=posi && matrix[line][posj])
				for(int col=0; col<n; ++col)
					matrix[line][col] = 0;
		}
		// column
		for(int col=0; col<n; ++col)
			if(col!=posj && matrix[posi][col])
				for(int line=0; line<m; ++line)
					matrix[line][col] = 0;
		
		// 
		for(int line=0; line<m; ++line)
			matrix[line][posj] = 0;
		for(int col=0; col<n; ++col)
			matrix[posi][col] = 0;
	}
};












































// pass 2
class Solution {
public:
	// find the first 0, use the row and column to record the rows and columns which has 0s
    void setZeroes(vector<vector<int> > &matrix) {
		int m = matrix.size();
		if(!m)
			return;
		int n = matrix[0].size();
		if(!n)
			return;
		
		int i = 0;
		int j = 0;
		for(; i<m; ++i) {
			bool bFound = false;
			for(j=0; j<n; ++j) 
				if(matrix[i][j] == 0) {
					bFound = true;
					break;
				}
			if(bFound)
				break;
		}
		
		if(i >= m)
			return;

		// For j column
		for(int p=0; p<m; ++p) {
			if(p == i)
				continue;
			
			// check all elements in the row
			bool bHasZero = false;
			for(int q=0; q<n; ++q)
				if(!matrix[p][q]) {
					bHasZero = true;
					break;
				}
			matrix[p][j] = bHasZero;
		}
		
		for(int q=0; q<n; ++q) {
			if(q == j)
				continue;
			bool bHasZero = false;
			for(int p=0; p<m; ++p)
				if(!matrix[p][q]) {
					bHasZero = true;
					break;
				}
			matrix[i][q] = bHasZero;
		}
		
		// use (i, j)
		// row i
		for(int p=0; p<m; ++p)
			for(int q=0; q<n; ++q) {
				if(p!=i && q!=j) {
					if(matrix[p][j])
						matrix[p][q] = 0;
					if(matrix[i][q])
						matrix[p][q] = 0;
				}
			}
		for(int k=0; k<m; ++k)
			matrix[k][j] = 0;
		for(int k=0; k<n; ++k)
			matrix[i][k] = 0;
    }
};






































class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix);
};



void Solution::setZeroes(vector<vector<int> > &matrix)
{
	int m = matrix.size();
	if(!m)
		return;
	int n = matrix[0].size();
	if(!n)
		return;
	
	int nMAXIMUM = 0;
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(nMAXIMUM < matrix[i][j])
				nMAXIMUM = matrix[i][j] + 1000;
				
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(!matrix[i][j])
				matrix[i][j] = nMAXIMUM;
				
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(matrix[i][j] == nMAXIMUM)
			{
				for(int k=0; k<n; ++k)
					if(matrix[i][k] != nMAXIMUM)
						matrix[i][k] = 0;
				for(int k=0; k<m; ++k)
					if(matrix[k][j] != nMAXIMUM)
						matrix[k][j] = 0;
			}
	
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(matrix[i][j] == nMAXIMUM)
				matrix[i][j] = 0;
}

