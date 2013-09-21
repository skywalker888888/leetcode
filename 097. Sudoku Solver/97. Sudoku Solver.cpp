/**
		Write a program to solve a Sudoku puzzle by filling the empty cells.

		Empty cells are indicated by the character '.'.

		You may assume that there will be only one unique solution.


		A sudoku puzzle...


		...and its solution numbers marked in red.
		
		see also: 98. Valid Sudoku
*/
// pass 3
class Solution {
public:
    void solveSudoku(vector<vector<char> > &board) {
		solveSudoku(board, 0, 0);
    }
	bool solveSudoku(vector<vector<char> > &board, int i, int j) {
		if(board[i][j] != '.') {
			if(i==8 && j==8)
				return true;
			bool bRet = false;
			if(j < 8)
				bRet = solveSudoku(board, i, j+1);
			else 
				bRet = solveSudoku(board, i+1, 0);
			return bRet;
		} else {
			string candidates = findCandidates(board, i, j);
			for(int k=0; k<candidates.size(); ++k) {
				board[i][j] = candidates[k];
				if(i==8 && j==8)
					return true;
				else {
					bool bRet = false;
					if(j < 8)
						bRet = solveSudoku(board, i, j+1);
					else 
						bRet = solveSudoku(board, i+1, 0);
					if(bRet)
						return true;
				}
				//if(validSolution(board))
			}
			board[i][j] = '.';
		}
		return false;
	}
	string findCandidates(vector<vector<char> > &board, int i, int j) {
		unordered_map<char, int> data;
		for(int k=0; k<9; ++k) {
			++data[board[i][k]];
			++data[board[k][j]];
		}
		
		string result;
		
		int i1 = i/3 * 3;
		int j1 = j/3 * 3;
		for(int ii=i1; ii<i1+3; ++ii)
			for(int jj=j1; jj<j1+3; ++jj)
				++data[board[ii][jj]];
		for(char ch='1'; ch<='9'; ++ch)
			if(data.find(ch) == data.end())
				result.push_back(ch);
		return result;
	}
	bool validSolution(vector<vector<char> > &board) {
		for(int i=0; i<9; ++i)
			for(int j=0; j<9; ++j)
				if(board[i][j] == '.')
					return false;
		return true;
	}
};



























// pass 2
class Solution {
public:
    void solveSudoku(vector<vector<char> > &board) {
    	solveSudoku(board, pair<int, int>(0,0));
    }
	
    bool solveSudoku(vector<vector<char> > &board, pair<int, int> pos) {
		while(pos.first<9 && board[pos.first][pos.second]!= '.')
			pos = getNextPosition(pos);
		if(pos.first >= 9)
			return true;
		
		vector<char> candidates = getCandidateChars(board, pos.first, pos.second);
		for(int i=0; i<candidates.size(); ++i) {
			board[pos.first][pos.second] = candidates[i];
			if(solveSudoku(board, pos))
				return true;
		}
		board[pos.first][pos.second] = '.';
		return false;
	}
	
	pair<int, int> getNextPosition(pair<int, int> pos) {
		if(pos.first >= 9)
			return pos;
		if(pos.second < 8)
			++pos.second;
		else {
			++pos.first;
			pos.second = 0;
		}
		
		return pos;
	}


	vector<char> getCandidateChars(vector<vector<char> > &board, int i, int j)
	{
		int m = board.size();
		int n = board[0].size();

		vector<char> result;
		if(board[i][j] != '.')
			return result;
		
		 //
		 for(int k=0; k<9; ++k)
			result.push_back(k + '1');
			
		// remove the line 
		for(int k=0; k<9; ++k)
		{
			char ch = board[i][k];
			vector<char>::iterator itr = find(result.begin(), result.end(), ch);
			if(itr != result.end())
				result.erase(itr);
		}
		
		// column
		for(int k=0; k<9; ++k)
		{
			char ch = board[k][j];
			vector<char>::iterator itr = find(result.begin(), result.end(), ch);
			if(itr != result.end())
				result.erase(itr);
		}
		
		// sub rectangle
		for(int a=0; a<m; a+=3)
			for(int b=0; b<n; b+=3)
				if(a<=i && a+2>=i && b<=j && b+2>=j)
					for(int u=a; u<=a+2; ++u)
						for(int v=b; v<=b+2; ++v) {
							char ch = board[u][v];
							vector<char>::iterator itr = find(result.begin(), result.end(), ch);
							if(itr != result.end())
								result.erase(itr);
						}
		return result;
	}
};






























class Solution {
public:

	void solveSudoku(vector<vector<char> > &board) {
		solveSudoku(board, pair<int, int>(0, 0));
	}


	bool solveSudoku(vector<vector<char> > &board, pair<int, int> pos)
	{
		int m = board.size();
		int n = board[0].size();
		
		while(pos.first<m && board[pos.first][pos.second]!='.')
			pos = getNextPosition(pos);
		
		if(pos.first >= m)
			return true;
			
		vector<char> candidates = getCandidateChars(board, pos.first, pos.second);
		for(int k=0; k<candidates.size(); ++k) {
			board[pos.first][pos.second] = candidates[k];
			if(solveSudoku(board, pos))
				return true;
		}
		board[pos.first][pos.second] = '.';
		
		return false;
	}


	pair<int, int> getNextPosition(pair<int, int> pos) {
		if(pos.first >= 9)
			return pos;
		if(pos.second < 8)
			++pos.second;
		else {
			++pos.first;
			pos.second = 0;
		}
		
		return pos;
	}
	
	vector<char> getCandidateChars(vector<vector<char> > &board, int i, int j)
	{
		int m = board.size();
		int n = board[0].size();

		vector<char> result;
		if(board[i][j] != '.')
			return result;
		 //
		 for(int k=0; k<9; ++k)
			result.push_back(k + '1');
		// remove the line 
		for(int k=0; k<9; ++k)
		{
			char ch = board[i][k];
			vector<char>::iterator itr = find(result.begin(), result.end(), ch);
			if(itr != result.end())
				result.erase(itr);
		}
		
		// column
		for(int k=0; k<9; ++k)
		{
			char ch = board[k][j];
			vector<char>::iterator itr = find(result.begin(), result.end(), ch);
			if(itr != result.end())
				result.erase(itr);
		}
		
		// sub rectangle
		for(int a=0; a<m; a+=3)
			for(int b=0; b<n; b+=3)
				if(a<=i && a+2>=i && b<=j && b+2>=j)
					for(int u=a; u<=a+2; ++u)
						for(int v=b; v<=b+2; ++v)
						{
							char ch = board[u][v];
							vector<char>::iterator itr = find(result.begin(), result.end(), ch);
							if(itr != result.end())
								result.erase(itr);
						
						}
						
		return result;
	}
};














class Solution {
public:

	void solveSudoku(vector<vector<char> > &board) {
		solveSudoku(board, 0, 0);
	}


	bool solveSudoku(vector<vector<char> > &board, int i, int j)
	{
		int m = board.size();
		int n = board[0].size();
		
		char ch = board[i][j];
		if(ch != '.') {
			if(i==m-1 && j==n-1)
				return true;
			else if(i == m-1)
				return solveSudoku(board, i, j+1);
			else if(j==n-1)
				return solveSudoku(board, i+1, 0);
			else
				return solveSudoku(board, i, j+1);
		} else {
			vector<char> candidates = getCandidateChars(board, i, j);
			for(int k=0; k<candidates.size(); ++k) {
				board[i][j] = candidates[k];
				if(solveSudoku(board, i, j))
					return true;
			}
			board[i][j] = '.';
			return false;
		}
	}


	vector<char> getCandidateChars(vector<vector<char> > &board, int i, int j)
	{
		int m = board.size();
		int n = board[0].size();

		vector<char> result;
		if(board[i][j] != '.')
			return result;
		
		 //
		 for(int k=0; k<9; ++k)
			result.push_back(k + '1');
			
		// remove the line 
		for(int k=0; k<9; ++k)
		{
			char ch = board[i][k];
			vector<char>::iterator itr = find(result.begin(), result.end(), ch);
			if(itr != result.end())
				result.erase(itr);
		}
		
		// column
		for(int k=0; k<9; ++k)
		{
			char ch = board[k][j];
			vector<char>::iterator itr = find(result.begin(), result.end(), ch);
			if(itr != result.end())
				result.erase(itr);
		}
		
		// sub rectangle
		for(int a=0; a<m; a+=3)
			for(int b=0; b<n; b+=3)
				if(a<=i && a+2>=i && b<=j && b+2>=j)
					for(int u=a; u<=a+2; ++u)
						for(int v=b; v<=b+2; ++v)
						{
							char ch = board[u][v];
							vector<char>::iterator itr = find(result.begin(), result.end(), ch);
							if(itr != result.end())
								result.erase(itr);
						
						}
						
		return result;
	}

	bool isValidSudoku(vector<vector<char> > &board)
	{
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
			for(int j=0; j<n; j+=3)
			{
				if(!validRectangle(board, i, j, i+2, j+2))
					return false;
			}
			
		return true;
	}

	bool validRectangle(vector<vector<char> > &board, int a1, int b1, int a2, int b2)
	{
		// each line must not have duplicate number and numbers must be in 1..9
		for(int i=a1; i<=a2; ++i)
		{
			for(int j=b1; j<=b2; ++j)
			{
				char ch = board[i][j];
				if(ch != '.')
					if(ch>'9' || ch<'1')
						return false;
					else
					{
						for(int k=j+1; k<=b2; ++k)
							if(ch == board[i][k])
								return false;
						for(int ii=i+1; ii<=a2; ++ii)
							for(int jj=b1; jj<=b2; ++jj)
							if(ch == board[ii][jj])
								return false;
					}
			}
		}
		return true;
	}
};

