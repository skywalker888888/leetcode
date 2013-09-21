/**
		The n-queens puzzle is the problem of placing n queens on an nxn chessboard such that no two queens attack each other.
		A queen can attack other queen if they are at the same line horizontally, vertically or diagnotically.

		Given an integer n, return all distinct solutions to the n-queens puzzle.

		Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

		For example,
		There exist two distinct solutions to the 4-queens puzzle:

		[
		 [".Q..",  // Solution 1
		  "...Q",
		  "Q...",
		  "..Q."],

		 ["..Q.",  // Solution 2
		  "Q...",
		  "...Q",
		  ".Q.."]
		]
		
		See also: 82. N-Queens II
*/
// pass 3
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
		vector<vector<string> > result;
		if(!n)
			return result;
			
		vector<string> item(n, string(n, '.'));
		solveNQueens(n, item, 0, result);
		return result;
    }
	
	void solveNQueens(int n, vector<string> &item, int line, vector<vector<string> > &result) {
		for(int i=0; i<n; ++i) {
			if( canPutQueen(n, item, line, i) ) {
				item[line][i] = 'Q';
				if(line == n-1)
					result.push_back(item);
				else
					solveNQueens(n, item, line+1, result);
				item[line][i] = '.';
			}
		}
	}
	
	bool canPutQueen(int n, vector<string> &item, int i, int j) {
		for(int k=0; k<n; ++k) {
			// - direction
			if(k!=j && item[i][k]=='Q')
				return false;
			// | direction
			if(k!=i && item[k][j]=='Q')
				return false;
			
			// / direction
			if(k!=0 && j+k<n && i-k>=0 && item[i-k][j+k]=='Q')
				return false;
			
			// \ direction
			if(k!=0 && i-k>=0 && j-k>=0  && item[i-k][j-k]=='Q')
				return false;
		}
		return true;
	}
};






































// pass 2
class Solution {
public:
	bool canPutQueen(const vector<string> &board, int i, int j) {
		int n = board.size();
		if(!n)
			return false;
			
		if(board[i][j] == 'Q')
			return false;
			
		// - direction
		for(int k=0; k<n; ++k)
			if(board[i][k] == 'Q')
				return false;
				
		// | direction
		for(int k=0; k<n; ++k)
			if(board[k][j] == 'Q')
				return false;
		
		// \ direction
		for(int k=1; k<n; ++k)
			if(i+k<n && j+k<n && board[i+k][j+k]=='Q')
				return false;
			else if(i-k>=0 && j-k>=0 && board[i-k][j-k]=='Q')
				return false;
				
		// / direction
		for(int k=1; k<n; ++k)
			if(i+k<n && j-k>=0 && board[i+k][j-k]=='Q')
				return false;
			else if(i-k>=0 && j+k<n && board[i-k][j+k]=='Q')
				return false;
				
		return true;
	}
	
    vector<vector<string> > solveNQueens(int n) {
		vector<vector<string> > result;
		if(!n)
			return result;
		
		vector<string> board(n, string(n, '.'));
		result = solveNQueens(board, 0);
    }
	
    vector<vector<string> > solveNQueens(vector<string> &board, int linenum) {
		int n = board.size();
		vector<vector<string> > result;
		if(linenum >= n) {
			result.push_back(board);
			return result;
		}
		
		for(int i=0; i<n; ++i) {
			if(canPutQueen(board, linenum, i)) {
				board[linenum][i] = 'Q';
				vector<vector<string> > result1 = solveNQueens(board, linenum+1);
				result.insert(result.end(), result1.begin(), result1.end());
				board[linenum][i] = '.';
			}
		}
		
		return result;
	}
};












































class Solution {
public:
	vector<vector<string> > solveNQueens(int n) {
		vector<vector<string> > result;
		
		vector<int> selectedColumns(n, -1);
		DFS(selectedColumns, 0, result);
		
		return result;
	}
	void DFS(vector<int> &selectedColumns, int nDepth, vector<vector<string> >& result) {
		int n = selectedColumns.size();
		if(nDepth == n)
			appendStrings(result, selectedColumns);
		else
			for(int i=0; i<n; ++i)
				if(isValidPosition(selectedColumns, nDepth, i)) {
					selectedColumns[nDepth] = i;
					DFS(selectedColumns, nDepth+1, result);
				}
				
	}

	void appendStrings(vector<vector<string> >& result, const vector<int> &selectedColumns) {
		vector<string> item;
		int n = selectedColumns.size();
		for(int d=0; d<n; ++d) {
			int x = d;
			int y = selectedColumns[x];
			string str = generateString( n, x, y );
			item.push_back(str);
		}
		
		result.push_back(item);
	}
	
	bool isValidPosition(vector<int> &selectedColumns, int nDepth, int nIndex) {
		for(int d=0; d<nDepth; ++d) {
			int x = d;
			int y = selectedColumns[x];
			
			int i = nDepth;
			int j = nIndex;
			
			if(y == j)
				return false;
			if(abs(x-i) == abs(y-j))
				return false;
		}
		
		return true;
	}
	
	
	string	generateString(int n, int i, int j) {
		string str;
		for(int k=0; k<j; ++k)
			str.push_back('.');
		str.push_back('Q');
		for(int k=j+1; k<n; ++k)
			str.push_back('.');
			
		return str;
	}

};




class Solution {
public:
	vector<vector<string> > solveNQueens(int n) {
		vector<vector<string> > result;
		
		if(!n)
			return result;
			
		vector<vector<int> > matrix(n, vector<int>(n, 0));
		vector<string> tmpStr;
		for(int j=0; j<n; ++j) {
			vector<vector<string> > resi = solveNQueensSub(n, 0, j, matrix, tmpStr);
			result.insert(result.end(), resi.begin(), resi.end());
		}
		
		return result;
	}

	vector<vector<string> > solveNQueensSub(int n, int i, int j, vector<vector<int> >& matrix, vector<string> tmpStr)
	{
		vector<vector<string> > result;
		
		// 
		string str = generateString(n, i, j);
		tmpStr.push_back(str);
		if(i == n-1)
		{
			result.push_back(tmpStr);
			return result;
		}
		
		encreaseAttackNumber(matrix, n, i, j);
		for(int k=0; k<n; ++k)
		{
			if(!matrix[i+1][k])
			{
				vector<vector<string> > re = solveNQueensSub(n, i+1, k, matrix, tmpStr);
				result.insert(result.end(), re.begin(), re.end()); 
			}
		}
		decreaseAttackNumber(matrix, n, i, j);
		
		return result;
	}
	
	string	generateString(int n, int i, int j) {
		string str;
		for(int k=0; k<j; ++k)
			str.push_back('.');
		str.push_back('Q');
		for(int k=j+1; k<n; ++k)
			str.push_back('.');
			
		return str;
	}

	void encreaseAttackNumber(vector<vector<int> >& matrix, int n, int i, int j) {
		for(int k=0; k<n; ++k) {
			++matrix[i][k];
			++matrix[k][j];
		}
		
		int x = i-1;
		int y = j-1;
		while(x>=0 && y>=0) {
			++matrix[x][y];
			--x;
			--y;
		}
		x = i+1;
		y = j+1;
		while(x<n && y<n) {
			++matrix[x][y];
			++x;
			++y;
		}
		
		// left down
		x = i+1;
		y = j-1;
		while(x<n && y>=0) {
			++matrix[x][y];
			++x;
			--y;
		}
		// right up
		x = i-1;
		y = y+1;
		while(x>=0 && y<n) {
			++matrix[x][y];
			--x;
			++y;
		}
	}

	void decreaseAttackNumber(vector<vector<int> >& matrix, int n, int i, int j)
	{
		for(int k=0; k<n; ++k) {
			--matrix[i][k];
			--matrix[k][j];
		}

		// left top 
		int x = i-1;
		int y = j-1;
		while(x>=0 && y>=0) {
			--matrix[x][y];
			--x;
			--y;
		}
		
		// bottom down
		x = i+1;
		y = j+1;
		while(x<n && y<n) {
			--matrix[x][y];
			++x;
			++y;
		}
		
		// left down
		x = i+1;
		y = j-1;
		while(x<n && y>=0) {
			--matrix[x][y];
			++x;
			--y;
		}
		
		// right up
		x = i-1;
		y = y+1;
		while(x>=0 && y<n) {
			--matrix[x][y];
			--x;
			++y;
		}
	}
};






