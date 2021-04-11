/**
		Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules. http://sudoku.com.au/TheRules.aspx

		The Sudoku board could be partially filled, where empty cells are filled with the character '.'.


		A partially filled sudoku which is valid.

		// see also: 97. Sudoku Solver
*/
// pass 3
class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
    	int n = board.size();
		if(n != 9)
			return false;
		unordered_map<char, int> data;
		// check lines
		for(int i=0; i<n; ++i) {
			data.clear();
			if(board[i].size() != n)
				return false;
			for(int j=0; j<n; ++j) {
				if((board[i][j]<'1'||board[i][j]>'9' ) && (board[i][j]!='.'))
					return false;
				++data[board[i][j]];
			}
			for(char ch='1'; ch<='9'; ++ch)
				if(data.find(ch)!=data.end() && data[ch]>1)
					return false;
		}
		
		// columns
		for(int j=0; j<n; ++j) {
			data.clear();
			for(int i=0; i<n; ++i)
				++data[board[i][j]];
			for(char ch='1'; ch<='9'; ++ch)
				if(data.find(ch)!=data.end() && data[ch]>1)
					return false;
		}
		
		// cubs
		for(int i=0; i<n; i+=3) {
			for(int j=0; j<n; j+=3) {
				// (i, j) & (i+2, j+2)
				data.clear();
				for(int ii=i; ii<i+3; ++ii)
					for(int jj=j; jj<j+3; ++jj)
						++data[board[ii][jj]];
				for(char ch='1'; ch<='9'; ++ch)
					if(data.find(ch)!=data.end() && data[ch]>1)
						return false;
			}
		}
		return true;
    }
};






























// pass 2
class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
    	int n = board.size();
		if(n != 9)
			return false;
		for(int i=0; i<9; ++i)
			if(board[i].size() != 9)
				return false;
		for(int i=0; i<n; ++i)
			if(!isValidRectangle(board, i, 0, i, 8))
				return false;
		for(int i=0; i<n; ++i)
			if(!isValidRectangle(board, 0, i, 8, i))
				return false;
		for(int i=0; i<9; i+=3)
			for(int j=0; j<9; j+=3)
				if(!isValidRectangle(board, i, j, i+2, j+2))
					return false;
		return true;
	}
	
	bool isValidRectangle(vector<vector<char> > &board, int i, int j, int m, int n) {
		vector<bool> bol(9, false);
		for(int p=i; p<=m; ++p)
			for(int q=j; q<=n; ++q)
				if(board[p][q] != '.')
					if(board[p][q]<'1' || board[p][q]>'9')
						return false;
					else {
						int val = board[p][q]-'0'-1;
						if(bol[val])
							return false;
						bol[val] = true;
					}
		return true;
	}
};









































class Solution {
public:
	bool isValidSudoku(vector<vector<char> > &board) {
		int m = board.size();
		if(m != 9)
			return false;
		
		for(int i=0; i<m; ++i)
			if(board[i].size() != 9)
				return false;
		
		int n = board[0].size();
		
		// line
		for(int i=0; i<m; ++i)
			if(!validRectangle(board, i, 0, i, 8))
				return false;
				
		// column
		for(int j=0; j<n; ++j)
			if(!validRectangle(board, 0, j, 8, j))
				return false;
		
		
		// check the 9 sub-arrayss
		for(int i=0; i<m; i+=3)
			for(int j=0; j<n; j+=3) {
				if(!validRectangle(board, i, j, i+2, j+2))
					return false;
			}
			
		return true;
	}

	bool validRectangle(vector<vector<char> > &board, int a1, int b1, int a2, int b2)
	{
		// each line must not have duplicate number and numbers must be in 1..9
		for(int i=a1; i<=a2; ++i)
			for(int j=b1; j<=b2; ++j) {
				char ch = board[i][j];
				if(ch != '.')
					if(ch>'9' || ch<'1')
						return false;
					else {
						for(int k=j+1; k<=b2; ++k)
							if(ch == board[i][k])
								return false;
						for(int ii=i+1; ii<=a2; ++ii)
							for(int jj=b1; jj<=b2; ++jj)
							if(ch == board[ii][jj])
								return false;
					}
			}
		return true;
	}
};



