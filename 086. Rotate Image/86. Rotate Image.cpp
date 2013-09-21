/**
		You are given an n x n 2D matrix representing an image.

		Rotate the image by 90 degrees (clockwise).

		Follow up:
		Could you do this in-place?
*/
// pass 3
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
		int n = matrix.size();
		if(!n)
			return;
		
		int i1=0, j1=0;
		int i2=n-1, j2=n-1;
		
		while(i1<i2) {
			for(int k=j1; k<j2; ++k) {
				// (i1, k) ==> (i1+(k-j1), j2)
				int tmp = matrix[i1+(k-j1)][j2];
				matrix[i1+(k-j1)][j2] = matrix[i1][k];

				// (i1+(k-j1), j2) ==> (i2, j2-(k-j1))
				int tmp2 = matrix[i2][j2-(k-j1)];
				matrix[i2][j2-(k-j1)] = tmp;
				
				// (i2, j2-(k-j1)) ==> (i2-(k-j1), j1)
				int tmp3 = matrix[i2-(k-j1)][j1];
				matrix[i2-(k-j1)][j1] = tmp2;
				
				// (i2-(k-j1), j1) ==> (i1, k)
				matrix[i1][k] = tmp3;
			}
			++i1, ++j1, --i2, --j2;
		}
    }
};














































// pass 2
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
		int m = matrix.size();
		if(!m)
			return;
		int n = matrix[0].size();
		if(m != n)
			return;
		
		int i1=0, j1=0;
		int i2=n-1, j2=n-1;
		
		while(i1 <= i2) {
			
			for(int k=j1; k<j2; ++k) {
				// (i1, k) ==> (i1+(k-j1), j2)
				int val1 = matrix[i1+(k-j1)][j2];
				matrix[i1+(k-j1)][j2] = matrix[i1][k];
				
				// (i1+(k-j1), j2) ==> (i2, j2-(k-j1))
				int val2 = matrix[i2][j2-(k-j1)];
				matrix[i2][j2-(k-j1)] = val1;
				
				// (i2, j2-(k-j1)) ==> (i2-(k-j1), j1) 
				int val3 = matrix[i2-(k-j1)][j1];
				matrix[i2-(k-j1)][j1] = val2;
				
				// (i2-(k-j1), j1) ==> (i1, k)
				matrix[i1][k] = val3;
			}
		
			++i1, ++j1, --i2, --j2;
		}
    }
};










































class Solution {
public:
	void rotate(vector<vector<int> > &matrix) {
		int n = matrix.size();
		if(n <= 1)
			return;
		rotate(0, 0, n-1, n-1, matrix);
	}
	void rotate(int i, int j, int x, int y, vector<vector<int> > &matrix) {
		if(i>=x)
			return;
		
		int n = j - i + 1;
		
		rotate(i+1, j+1, x-1, y-1, matrix);
		
		for(int k=j; k<y; ++k) {
			// (i, k)
			int val = matrix[i][k];
			int val2;
			
			// top to right (i, k)==>()
			int i1 = i+(k-j);
			int j1 = y;
			val2 = matrix[i1][j1];
			matrix[i1][j1] = val;
			val = val2;
			
			// right to bottom
			int i2 = x;
			int j2 = j+(x-i1);
			val2 = matrix[i2][j2];
			matrix[i2][j2] = val;
			val = val2;

			// bottom to left
			int i3 = i+(j2-j);
			int j3 = j;
			val2 = matrix[i3][j3];
			matrix[i3][j3] = val;
			val = val2;
			
			// left to top
			int i4 = i;
			int j4 = k;
			val2 = matrix[i4][j4];
			matrix[i4][j4] = val;
			val = val2;
		}
	}
};



