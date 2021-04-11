/**
		Given an integer n, generate a square matrix filled with elements from 1 to n^2 in spiral order.

		For example,
		Given n = 3,

		You should return the following matrix:
		[
		 [ 1, 2, 3 ],
		 [ 8, 9, 4 ],
		 [ 7, 6, 5 ]
		]
		
		See also: 80. Spiral Matrix
*/
// pass 3
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
		vector<vector<int> > result(n, vector<int>(n, 1));
		if(n < 2)
			return result;
		
		int i1=0, j1=0;
		int i2=n-1, j2=n-1;
		
		int num = 1;
		while(i1<=i2 && j1<=j2) {
			// left => right
			for(int k=j1; k<=j2; ++k)
				result[i1][k] = num++;
			if(i1 == i2)
				break;
			
			// top ==> bottom
			for(int k=i1+1; k<=i2; ++k)
				result[k][j2] = num++;
			if(j1 == j2)
				break;
			
			// right=>left
			for(int k=j2-1; k>=j1; --k)
				result[i2][k] = num++;
			
			// bottom => top
			for(int k=i2-1; k>i1; --k)
				result[k][j1] = num++;
		
			++i1, ++j1, --i2, --j2;
		}
		
		return result;
    }
};




































// pass 2
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
		vector<vector<int> > result(n, vector<int>(n, 0));
		int i1, j1, i2, j2;
		i1 = j1 = 0;
		i2 = j2 = n-1;
		int num = 1;
		while(i1 <= i2) {
			// (i1, j1) ==> (i1, j2)
			for(int k=j1; k<=j2; ++k)
				result[i1][k] = num++;
			
			// (i1, j2) ==> (j2, j2)
			for(int k=i1+1; k<=i2; ++k)
				result[k][j2] = num++;
			
			// (i2, j2) ==> (i2, j1)
			for(int k=j2-1; k>=j1; --k)
				result[i2][k] = num++;
			
			// (i2, j1) ==> (i1, j1)
			for(int k=i2-1; k>i1; --k)
				result[k][j1] = num++;
			
			++i1, ++j1, --i2, --j2;
		}
		
		return result;
    }
};









































class Solution {
public:
	vector<vector<int> > generateMatrix(int n) {
		vector<vector<int> > result;
		if(n <= 0)
			return result;
		
		result = vector<vector<int> >(n, vector<int>(n, 0));
		int a = 0;
		int b = 0;
		int c = n-1;
		int d = n-1;
		int direction = 0; // left first
		int x = a;
		int y = b;
		for(int i=1; i<n*n+1; ++i) {
			result[x][y] = i;
			if(x==a+1 && y==b && direction==3) {
				++a; ++b; --c; --d;
				if(a>c || b>d)
					break;
				
				x = a;
				y = b;
				direction = 0;
			} else {
				switch(direction) {
				case 0: // right
					if(y+1<=d)
						++y;
					else if(x+1 <= c) {
						 // down
						++x;
						direction = 1;
					}
					break;
				case 1: // down
					if(x+1 <= c)
						++x;
					else if(y-1 >= b) {
						// left
						--y;
						direction = 2;
					}
					break;
				case 2:
					if(y-1 >= b) // left
						--y;
					else if(x-1 > a) {
						--x;
						direction = 3;
					}
					break;
				case 3:
					if(x-1 > a)
						--x;
					break;
				}
			}
		}
		
		return result;
	}
};


