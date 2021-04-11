/**
		Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

		For example,
		Given the following matrix:

		[
		 [ 1, 2, 3 ],
		 [ 4, 5, 6 ],
		 [ 7, 8, 9 ]
		]
		You should return [1,2,3,6,9,8,7,4,5].
		
		See also: 75. Spiral Matrix II
*/
// pass 3
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
		vector<int> result;
		int m = matrix.size();
		if(!m)
			return result;
		int n = matrix[0].size();
		if(!n)
			return result;
		
		int i1=0, j1=0;
		int i2=m-1, j2=n-1;
		while(i1<=i2 && j1<=j2) {
			// left -> right
			for(int j=j1; j<=j2; ++j)
				result.push_back(matrix[i1][j]);
			if(i1 == i2)
				break;
			
			// top -> bottom
			for(int i=i1+1; i<=i2; ++i)
				result.push_back(matrix[i][j2]);
			if(j1 == j2)
				break;
			
			// right -> left
			for(int j=j2-1; j>=j1; --j)
				result.push_back(matrix[i2][j]);
				
			// bottom -> top
			for(int i=i2-1; i>i1; --i)
				result.push_back(matrix[i][j1]);
				
			++i1, ++j1, --i2, --j2;
				
		}
		return result;
    }
};































// pass 2
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
		vector<int> result;
		int m = matrix.size();
		if(!m)
			return result;
		int n = matrix[0].size();
		if(!n)
			return result;
		int i1=0, j1=0, i2=m-1, j2=n-1;
		while(i1<=i2 && j1<=j2) {
			// (i1, j1) ==> (i1, j2)
			for(int k=j1; k<=j2; ++k)
				result.push_back(matrix[i1][k]);
			// (i1, j2) ==> (i2, j2)
			for(int k=i1+1; k<=i2; ++k)
				result.push_back(matrix[k][j2]);
			
			// (i2, j2) ==> (i2, j1)
			for(int k=j2-1; i1!=i2 && k>=j1; --k)
				result.push_back(matrix[i2][k]);
			
			// (i2, j1) == (i1, j1)
			for(int k=i2-1; j1!=j2 && k>i1; --k)
				result.push_back(matrix[k][j1]);
			
			++i1, ++j1, --i2, --j2;
		}
		return result;
    }
};











































class Solution {
public:
	vector<int> spiralOrder(vector<vector<int> > &matrix)
	{
		vector<int> result;

		int m = matrix.size();
		if(!m)
			return result;
			
		int n = matrix[0].size();
		if(!n)
			return result;
		
		//vector<vector<bool> > visited(m, vector<bool>(n, false));
		
		int nDirection = 0;
		
		int a = 0, b = 0, c = m-1, d = n-1;
		int i = a;
		int j = b;

		int direction = 0;
		while(true)
		{
			result.push_back(matrix[i][j]);
			// if finished a loop 
			if(i==a+1 && j==b && direction==3)
			{
				++a; ++b;
				--c; --d;
				if(a>c || b>d)
					return result;
				
				i = a;
				j = b;
				
				direction = 0;
				continue;
			}
			
			switch(direction)
			{
			case 0:
				if(j+1<=d) // right
					++j;
				else
					if(i+1 <= c)
					{
						direction = 1;
						++i;
					}
					else
						return result;
				break;
			case 1: // down
				if(i+1 <= c)
					++i;
				else if(j-1 >= b)
				{
					direction = 2;
					--j;
				}
				else
					return result;
				break;
			case 2: // left
				if(j-1 >= b)
					--j;
				else if(i-1 > a)
				{
					--i;
					direction = 3;
				}
				else
					return result;
				break;
			case 3: // up
				if(i-1 > a)
					--i;
				else 
					return result;
				break;
			}
		}
		
		return result;
	}
};




int main(int argc, char **argv)
{
	vector<vector<int> > matrix(4, vector<int>(4, 0));
	int val = 0;
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			matrix[i][j] = val++;
			
	Solution sol;
	vector<int> res = sol.spiralOrder(matrix);
}
