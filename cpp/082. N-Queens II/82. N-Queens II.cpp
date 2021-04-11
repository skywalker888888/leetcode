/**
		Follow up for N-Queens problem.
		Now, instead outputting board configurations, return the total number of distinct solutions.
		
		See also: 83. N-Queens
*/
// pass 3
class Solution {
public:
    int totalNQueens(int n) {
		if(!n)
			return 0;
		vector<int> cols(n, -1);
		int result = 0;
		
		stack<pair<int, int> > stkLines;
		stkLines.push(pair<int, int>(0, -1));
		while(!stkLines.empty()) {
			pair<int, int> &line = stkLines.top();
			
			bool bInserted = false;
			for(int col=line.second+1; col<n; ++col) {
				if(validSpot(line.first, col, cols)) {
					line.second = col;
					cols[line.first] = col;
					if(line.first == n-1) {
						++result;
					} else {
						bInserted = true;
						stkLines.push(pair<int, int>(line.first+1, -1));
						break;
					}
				}
			}
			if(!bInserted)
				stkLines.pop();
		}
		return result;
	}
	
	bool validSpot(int i, int j, vector<int> &cols) {
		for(int k=0; k<i; ++k) {
			if(cols[k] == j)
				return false;
			if(abs(k-i) == abs(cols[k]-j))
				return false;
		}
		
		return true;
	}
};




class Solution {
public:
    int totalNQueens(int n) {
		if(!n)
			return 0;
		// cols[i] = j, means there is a queen at (i, j) position, if j>=0 and j<n
		vector<int> cols(n, -1);
		int result = DFS(0, cols);
		return result;
    }
	
	int DFS(int line, vector<int> &cols) {
		int n = cols.size();
		int result = 0;
		for(int col=0; col<n; ++col) {
			if(validSpot(line, col, cols)) {
				cols[line] = col;
				if(line == n-1)
					++result;
				else
					result += DFS(line+1, cols);
			}
		}
		return result;
	}
	
	bool validSpot(int i, int j, vector<int> &cols) {
		for(int k=0; k<i; ++k) {
			if(cols[k] == j)
				return false;
			if(abs(k-i) == abs(cols[k]-j))
				return false;
		}
		
		return true;
	}
};



















































//  pass 2
class Solution {
public:
    int totalNQueens(int n) {
		if(!n)
			return 0;
		
		vector<int> cols(n, -1);
		int res = DFS(n, 0, cols);
		return res;
    }
	
	int DFS(int n, int i, vector<int> &cols) {
		if(i == n)
			return 1;
		int val = 0;
		for(int j=0; j<n; ++j) 
			if(isValidGrid(n, i, j, cols)) {
				cols[i] = j;
				val += DFS(n, i+1, cols);
			}
		
		return val;
	}
	
	bool isValidGrid(int n, int i, int j, const vector<int> &cols) {
		for(int k=0; k<i; ++k) {
			if(cols[k] == j)
				return false;
			if(abs(i-k) == abs(j-cols[k]))
				return false;
		}
		return true;
	}
};










































class Solution {
public:
	int totalNQueens(int n)
	{
		vector<int> result(n, -1);
		
		int nTotal = 0;
		DFS(0, result, nTotal);
		return nTotal;
	}
	void DFS(int depth, vector<int> &result, int &num)
	{
		int n = result.size();
		if(depth == n)
			++num;
		else
		{
			for(int i=0; i<n; ++i)
				if(itemIsValid(result, depth, i))
				{
					result[depth] = i;
					DFS(depth+1, result, num);
				}
		}
	}
	
	bool itemIsValid(vector<int> &result, int depth, int index)
	{
		for(int d=0; d<depth; ++d)
		{
			int x = d;
			int y = result[x];
			
			int i = depth;
			int j = index;
			
			if(y==j)
				return false;
			
			if(abs(x-i) == abs(y-j))
				return false;
		}
		
		return true;
	}
};


class Solution {
public:
	int totalNQueens(int n)
	{
		if(!n)
			return 0;
		
		int nTotal = 0;
		vector<vector<int> > attackNum(n, vector<int>(n, 0));
		for(int k=0; k<n; ++k)
		{
			int nNum = totalNQueensSub(n, 0, k, attackNum);
			nTotal += nNum;
		}
		
		return nTotal;
	}
	int totalNQueensSub(int n, int i, int j, vector<vector<int> > &matrix)
	{
		if(i==n-1)
			return 1;
		
		int nTotal = 0;
		adjustAttackerNum(n, i, j, matrix, 1);
		for(int k=0; k<n; ++k)
			if(!matrix[i+1][k])
			{
				int num = totalNQueensSub(n, i+1, k, matrix);
				nTotal += num;
			}
		adjustAttackerNum(n, i, j, matrix, -1);
			
		return nTotal;
	}
	void adjustAttackerNum(int n, int i, int j, vector<vector<int> > &matrix, int nInc)
	{
		for(int k=0; k<n; ++k)
		{
			matrix[i][k] += nInc;
			matrix[k][j] += nInc;
		}

		int x, y;
		// left up
		x = i-1;
		y = j-1;
		while(x>=0 && y>=0)
		{
			matrix[x][y] += nInc;
			--x;
			--y;
		}
		// left down
		x = i+1;
		y = j-1;
		while(x<n && y>=0)
		{
			matrix[x][y] += nInc;
			++x;
			--y;
		}
		
		// right up
		x = i-1;
		y = j+1;
		while(x>=0 && y<n)
		{
			matrix[x][y] += nInc;
			--x;
			++y;
		}
		
		// right down
		x = i+1;
		y = j+1;
		while(x<n && y<n)
		{
			matrix[x][y] += nInc;
			++x;
			++y;
		}
	}
};












