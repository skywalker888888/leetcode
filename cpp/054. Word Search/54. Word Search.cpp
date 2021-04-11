/**
		Given a 2D board and a word, find if the word exists in the grid.
		The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.
		For example,
		Given board =
		[
		  ["ABCE"],
		  ["SFCS"],
		  ["ADEE"]
		]
		word = "ABCCED", -> returns true,
		word = "SEE", -> returns true,
		word = "ABCB", -> returns false.
*/
// pass 3
// Non-recursion version
class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
    	int k = word.size();
		int m = board.size();
		if(!m)
			return !k;
		int n = board[0].size();
		if(!n)
			return !k;
		vector<vector<bool> > visited(m, vector<bool>(n, false));
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j) {
				stack<tuple<int, int, int, int> > stkNodes;
				stkNodes.push(tuple<int, int, int, int>(i, j, 0, 0));
				while(!stkNodes.empty()) {
					tuple<int, int, int, int> &node = stkNodes.top();
					if(board[std::get<0>(node)][std::get<1>(node)] != word[std::get<2>(node)]) {
						stkNodes.pop();
					}
					else if(std::get<2>(node) == k-1) {
						return true;
					}
					else {
						switch(std::get<3>(node)) {
						case 0:
							visited[std::get<0>(node)][std::get<1>(node)] = true;
							if(std::get<1>(node)+1<n && !visited[std::get<0>(node)][std::get<1>(node)+1]) {
								std::get<3>(node) = 1;
								stkNodes.push(tuple<int, int, int, int>(std::get<0>(node), std::get<1>(node)+1, std::get<2>(node)+1, 0));
								break;
							}
						case 1:
							if(std::get<1>(node)-1>=0 && !visited[std::get<0>(node)][std::get<1>(node)-1]) {
								std::get<3>(node) = 2;
								stkNodes.push(tuple<int, int, int, int>(std::get<0>(node), std::get<1>(node)-1, std::get<2>(node)+1, 0));
								break;
							}
						case 2:
							if(std::get<0>(node)-1>=0 && !visited[std::get<0>(node)-1][std::get<1>(node)]) {
								std::get<3>(node) = 3;
								stkNodes.push(tuple<int, int, int, int>(std::get<0>(node)-1, std::get<1>(node), std::get<2>(node)+1, 0));
								break;
							}
						case 3:
							if(std::get<0>(node)+1<m && !visited[std::get<0>(node)+1][std::get<1>(node)]) {
								std::get<3>(node) = 4;
								stkNodes.push(tuple<int, int, int, int>(std::get<0>(node)+1, std::get<1>(node), std::get<2>(node)+1, 0));
								break;
							}
						case 4:
							visited[std::get<0>(node)][std::get<1>(node)] = false;
							stkNodes.pop();
							break;
						}
					}
				}
			}
		return false;
	}
};

// Recursion version
class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
    	int k = word.size();
		int m = board.size();
		if(!m)
			return !k;
		int n = board[0].size();
		if(!n)
			return !k;
		vector<vector<bool> > visited(m, vector<bool>(n, false));
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(exist(board, i, j, word, 0, visited))
					return true;
		return false;
    }
    bool exist(vector<vector<char> > &board, int i, int j, string &word, int p, vector<vector<bool> > &visited) {
		int k = word.size();
		int m = board.size();
		int n = board[0].size();
		
		if(board[i][j] != word[p])
			return false;
		
		if(p == k-1)
			return true;
		
		visited[i][j] = true;
		// go right
		if(j+1<n && !visited[i][j+1] && exist(board, i, j+1, word, p+1, visited))
			return true;
		// go left
		if(j-1>=0 && !visited[i][j-1] && exist(board, i, j-1, word, p+1, visited))
			return true;
		// go up
		if(i-1>=0 && !visited[i-1][j] && exist(board, i-1, j, word, p+1, visited))
			return true;
		
		// go down
		if(i+1<m && !visited[i+1][j] && exist(board, i+1, j, word, p+1, visited))
			return true;
			
		visited[i][j] = false;
		
		return false;
	}
};











































// pass 2
class Solution {
public:
	enum _DIRECTION{
		DIR_NONE = 0,
		DIR_EAST = 1,
		DIR_SOUTH,
		DIR_WEST,
		DIR_NORTH,
	};
    bool exist(vector<vector<char> > &board, string word) {
		//
    	int w = word.size();
		if(!w)
			return true;
		
		int m = board.size();
		if(!m)
			return m==w;
		int n = board[0].size();
		if(!n)
			return n==w;
		
		// tuple<int, int, _DIRECTION, int> // (i, j), direction, and length
		vector<vector<bool> > visited(m, vector<bool>(n, false));
		stack<tuple<int, int, _DIRECTION, int> > stkNode;
		stkNode.push(tuple<int, int, _DIRECTION, int>(0, 0, DIR_NONE, 0));
		visited[0][0] = true;
		bool bRetrack = false;
		while(!stkNode.empty()){
			int i = std::get<0>(stkNode.top());
			int j = std::get<1>(stkNode.top());
			_DIRECTION dir = std::get<2>(stkNode.top());
			int ind = std::get<3>(stkNode.top());
			if(board[i][j]!=word[ind] || bRetrack){
				bRetrack = false;
				dir = DIR_NORTH; // stop on (i, j)
				while(dir == DIR_NORTH){
					visited[i][j] = false;
					stkNode.pop();
					if(stkNode.empty()) {
						if(j < n)
							++j;
						else if(i < m-1) {
							++i;
							j = 0;
						} else 
							break;
						// try different direction
						visited[i][j] = true;
						stkNode.push(tuple<int, int, _DIRECTION, int>(i, j, DIR_NONE, 0));
						break;
					} 
					i = std::get<0>(stkNode.top());
					j = std::get<1>(stkNode.top());
					dir = std::get<2>(stkNode.top());
					ind = std::get<3>(stkNode.top());
				}
			} else {
				// check next node
				bool checked = false;
				if(ind == word.size()-1)
					return true;
				
				while(!checked)
					switch(dir) {
						case DIR_NONE:
							dir = DIR_EAST;
							if(j < n-1 && !visited[i][j+1]){
								++j;
								visited[i][j] = true;
								
								std::get<2>(stkNode.top()) = dir;
								stkNode.push(tuple<int, int, _DIRECTION, int>(i, j, DIR_NONE, ind+1));
								checked = true;
							}
							break;
						case DIR_EAST:
							dir = DIR_SOUTH;
							if(i<m-1 && !visited[i+1][j]){
								++i;
								visited[i][j] = true;
								
								std::get<2>(stkNode.top()) = dir;
								stkNode.push(tuple<int, int, _DIRECTION, int>(i, j, DIR_NONE, ind+1));
								checked = true;
							}
							break;
						case DIR_SOUTH:
							dir = DIR_WEST;
							if(j>0 && !visited[i][j-1]){
								--j;
								visited[i][j] = true;
								
								std::get<2>(stkNode.top()) = dir;
								stkNode.push(tuple<int, int, _DIRECTION, int>(i, j, DIR_NONE, ind+1));
								checked = true;
							}
							break;
						case DIR_WEST:
							dir = DIR_NORTH;
							if(i>0 && !visited[i-1][j]){
								--i;
								visited[i][j] = true;
								
								std::get<2>(stkNode.top()) = dir;
								stkNode.push(tuple<int, int, _DIRECTION, int>(i, j, DIR_NONE, ind+1));
								checked = true;
							}
							break;
						case DIR_NORTH:
							// .......
							if(i==m-1 && j==n-1)
								return false;
							else{
								// not matching
								bRetrack = true;
								checked = true;
							}
							break;
					}
			}
		}
		
		return false;
    }
};





class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
    	int w = word.size();
		if(!w)
			return true;
		
		int m = board.size();
		if(!m)
			return m==w;
		int n = board[0].size();
		if(!n)
			return n==w;
		
		vector<vector<bool> > visited(m, vector<bool>(n, false));
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j){
				if( exist(board, i, j, visited, word, 0) )
					return true;
			}
		return  false;
    }
	
	bool exist(const vector<vector<char> > &board, int i, int j, vector<vector<bool> > &visited, const string &word, int pos){
		
		int m = board.size();
		int n = board[0].size();
		if(board[i][j] != word[pos])
			return false;
		if(pos == word.size()-1)
			return true;

		visited[i][j] = true;

		if(j+1<n  && !visited[i][j+1] && exist(board, i, j+1, visited, word, pos+1))
			return true;
		if(j-1>=0  && !visited[i][j-1] && exist(board, i, j-1, visited, word, pos+1))
			return true;
		
		if(i-1>=0 && !visited[i-1][j] && exist(board, i-1, j, visited, word, pos+1))
			return true;

			if(i+1<m && !visited[i+1][j] && exist(board, i+1, j, visited, word, pos+1))
			return true;
		
		visited[i][j] = false;
		return false;
	}
};
































class Solution
{
public:
	bool exist(vector<vector<char> > &board, string word)
	{
		if(word.empty())
			return true;

		int m = board.size();
		
		if(!m)
			return false;
		
		int n = board[0].size();
		if(!n)
			return false;
		vector<vector<bool> > bits(m, vector<bool>(n, false));
		
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
			{
				vector<vector<bool> > status = bits;
				if(board[i][j]==word[0] && exist(board, i, j, word, 0, status))
					return true;
			}
		return false;
	}


	bool exist(vector<vector<char> > &board, int i, int j, string& word, int k, vector<vector<bool> >& bits)
	{
		int m = board.size();
		int n = board[0].size();
		
		if(i>=m)
			return false;
		if(j >= n)
			return false;
		
		if(k >= word.size())
			return true;
		
		if(board[i][j] != word[k])
			return false;

		if(k >= word.size()-1)
			return true;
			
		bits[i][j] = true;
			
		// up
		if(i>0 && !bits[i-1][j] && board[i-1][j]==word[k+1])
		{
			bool exists = exist(board, i-1, j, word, k+1, bits);
			if(exists)
				return true;
		}
		
		// down
		if(i<m-1 && !bits[i+1][j] && board[i+1][j]==word[k+1])
		{
			bool exists = exist(board, i+1, j, word, k+1, bits);
			if(exists)
				return true;
		}
		
		// left
		if(j>0 && !bits[i][j-1] && board[i][j-1]==word[k+1])
		{
			bool exists = exist(board, i, j-1, word, k+1, bits);
			if(exists)
				return true;
		}
		
		// right
		if(j<n-1 && !bits[i][j+1] && board[i][j+1]==word[k+1])
		{
			bool exists = exist(board, i, j+1, word, k+1, bits);
			if(exists)
				return true;
		}
		
		bits[i][j] = false;
		
		return false;
	}
};


