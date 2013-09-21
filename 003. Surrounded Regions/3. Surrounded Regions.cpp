/*
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region .

For example,

X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/
// pass 3
// Time: O(m * n)
// Space: O(m * n)
class Solution {
public:
    void solve(vector<vector<char>> &board) {
		int m = board.size();
		if(!m)
			return;
		int n = board[0].size();
		if(!n)
			return;
			
		vector<vector<bool> > visited(m, vector<bool>(n, false));
		
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j)
				if(!visited[i][j] && board[i][j]=='O') {
					stack<pair<int, int> > stkNodes;
					queue<pair<int, int> > queNodes;
					stkNodes.push(pair<int, int>(i, j));
					visited[i][j] = true;
					bool bSurrounded = true;
					while(!stkNodes.empty()) {
						pair<int, int> pos = stkNodes.top();
						stkNodes.pop();
						queNodes.push(pos); // remember
						
						int ii = pos.first;
						int jj = pos.second;
						if(ii==0 || ii==m-1 || jj==0 || jj==n-1)
							bSurrounded = false;
						// go up
						if(ii-1>=0 && !visited[ii-1][jj] && board[ii-1][jj]==board[ii][jj]) {
							visited[ii-1][jj] = true;
							stkNodes.push(pair<int, int>(ii-1, jj));
						}
						// go down
						if(ii+1<m && !visited[ii+1][jj] && board[ii+1][jj]==board[ii][jj]) {
							visited[ii+1][jj] = true;
							stkNodes.push(pair<int, int>(ii+1, jj));
						}
						// go left
						if(jj-1>=0 && !visited[ii][jj-1] && board[ii][jj-1]==board[ii][jj]) {
							visited[ii][jj-1] = true;
							stkNodes.push(pair<int, int>(ii, jj-1));
						}
						// go right
						if(jj+1<n && !visited[ii][jj+1] && board[ii][jj+1]==board[ii][jj]) {
							visited[ii][jj+1] = true;
							stkNodes.push(pair<int, int>(ii, jj+1));
						}
					}
					
					// 
					if(bSurrounded) {
						while(!queNodes.empty()) {
							pair<int, int> pos = queNodes.front();
							int ii = pos.first;
							int jj = pos.second;
							board[ii][jj] = 'X';
							queNodes.pop();
						}
					}
				}
    }
};































#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stack>
#include <utility>

using namespace std;

/*
	3. Surrounded Regions
		Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
		A region is captured by flipping all 'O's into 'X's in that surrounded region .

		For example,
			X X X X
			X O O X
			X X O X
			X O X X
		After running your function, the board should be:

			X X X X
			X X X X
			X X X X
			X O X X
			

		Sample 2:
			X X X X X X X X X X X X X X X X
			X X X X X X X X X X X X X X X X
			O O X O X X X X X X X X X X X X
			X O X X X X X X X X X X X X X X
			X X X X X X X X X X X X X X X X
			X X O O O X X X X X X X X X X X
			X X X X O X X X X X X X X X X X
			X X X X O X X X X X X X X X X X
			X X X X O X X X X X O O O X X X
			X X X O X X X X X X O X O X X X
			O O O O X X X X X X O X O X X X
			X X X O X X X X X X O X O X X X
			X X X X X X X X X X O O O X X X
			X X X X X X X X X X X X X X X X
			X X X X X X X X X X X X X X X X
			X X X X X X X O X X X X X O X X
			X X X X X X X X X X X X X X O O
			
	Analysis:
		1. For each O char, we search for its four directions, if it there is a O adjecent, push the old O into stack and deep first to the new O.
			If there is one O that is on the edge, then this group are not surrounded by X. When there is no O can be found, then mark the whole group as visited.
			If there is no O that is on the edge, then this group are surrounded by X. When there is no O can be found, flip the char and make the whole group as visited
		
		2. do it without recursion
 */
 
class Solution {
public:
    void solve(vector<vector<char> > &board);
	bool	collectNode(vector<vector<char> > &board, vector<vector<bool> >& visited, vector<pair<int, int> > &nodes, int i, int j);
};

void Solution::solve(vector<vector<char> > &board)
{
	int m = board.size();
	if(!m) return;
	int n = board[0].size();
	if(!n) return;
	
	vector<vector<bool> > visited(m, vector<bool>(n, false));
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(!visited[i][j] && board[i][j]=='O')
			{
				vector<pair<int, int> > nodes;
				bool bSurrounded = collectNode(board, visited, nodes, i, j);
				if(bSurrounded)
				{
					for(int k=0; k<nodes.size(); ++k)
						board[nodes[k].first][nodes[k].second] = 'X';
				}
			}
	return;
}

bool Solution::collectNode(vector<vector<char> > &board, vector<vector<bool> >& visited, vector<pair<int, int> > &nodes, int i, int j)
{
	int m = board.size();
	int n = board[0].size();
	bool bSurrounded = true;
	visited[i][j] = true;
	if(i==0 || i==m-1 || j==0 || j==n-1)
		bSurrounded = false;
	
	nodes.push_back(pair<int, int>(i, j));
	if(i>0 && !visited[i-1][j] && board[i-1][j]=='O')
	{
		bool bTure = collectNode(board, visited, nodes, i-1, j);
		bSurrounded = bSurrounded && bTure;
	}
	if(i<m-1 && !visited[i+1][j] && board[i+1][j]=='O')
	{
		bool bTure = collectNode(board, visited, nodes, i+1, j);
		bSurrounded = bSurrounded && bTure;
	}
	
	if(j>0 && !visited[i][j-1] && board[i][j-1]=='O')
	{
		bool bTure = collectNode(board, visited, nodes, i, j-1);
		bSurrounded = bSurrounded && bTure;
	}
	
	if(j<n-1 && !visited[i][j+1] && board[i][j+1]=='O')
	{
		bool bTure = collectNode(board, visited, nodes, i, j+1);
		bSurrounded = bSurrounded && bTure;
	}
	
		
	return bSurrounded;
}


class Solution {
public:
    void solve(vector<vector<char> > &board);
};

void Solution::solve(vector<vector<char> > &board)
{
	int m = board.size();
	if(!m) return;
	int n = board[0].size();
	if(!n) return;
	
	vector<vector<bool> > visited(m, vector<bool>(n, false));
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(!visited[i][j] && board[i][j]=='O')
			{
				stack<pair<int,int> > stkNodes;
				vector<pair<int, int> > nodes;
				stkNodes.push(pair<int, int>(i, j));
				visited[i][j] = true;
				nodes.push_back(pair<int, int>(i, j));
				bool bSurounded = true;
				while(!stkNodes.empty())
				{
					pair<int, int> &pos = stkNodes.top();
					if(pos.first==0 || pos.first==m-1 || pos.second==0 || pos.second==n-1)
						bSurounded = false;
					int i = pos.first;
					int j = pos.second;
					if(i>0 && !visited[i-1][j] && board[i-1][j]=='O')
					{
						stkNodes.push(pair<int, int>(i-1, j));
						nodes.push_back(pair<int, int>(i-1, j));
						visited[i-1][j] = true;
						continue;
					}
					if(i<m-1 && !visited[i+1][j] && board[i+1][j]=='O')
					{
						stkNodes.push(pair<int, int>(i+1, j));
						nodes.push_back(pair<int, int>(i+1, j));
						visited[i+1][j] = true;
						continue;
					}
					
					if(j>0 && !visited[i][j-1] && board[i][j-1]=='O')
					{
						stkNodes.push(pair<int, int>(i, j-1));
						nodes.push_back(pair<int, int>(i, j-1));
						visited[i][j-1] = true;
						continue;
					}
					
					if(j<n-1 && !visited[i][j+1] && board[i][j+1]=='O')
					{
						stkNodes.push(pair<int, int>(i, j+1));
						nodes.push_back(pair<int, int>(i, j+1));
						visited[i][j+1] = true;
						continue;
					}
					stkNodes.pop();
				}
				if(bSurounded)
				{
					for(int k=0; k<nodes.size(); ++k)
						board[nodes[k].first][nodes[k].second] = 'X';
				}
			}
	
}






























enum NODE_COLOR
{
	E_COLOR_WHILE,
	E_COLOR_GREY, 
	E_COLOR_BLACK,
};

 
class Node
{
public:
	Node(char cChar)
		: m_cChar(cChar), m_eNodeColor(E_COLOR_WHILE)
		{}
	
	void				setCharValue(char cChar) { m_cChar = cChar; }
	const char			getCharValue() const{ return m_cChar; };
	bool				isBigX(){ return m_cChar=='X'; }
	bool				isBigO(){ return m_cChar=='O'; }
	
	void				setNodeColor(const NODE_COLOR eColor) {m_eNodeColor=eColor;}
	const NODE_COLOR	getNodeColor() const {return m_eNodeColor;}
	bool				isVisited() { return m_eNodeColor!=E_COLOR_WHILE;}
	
private:

private:
	char		m_cChar;
	NODE_COLOR	m_eNodeColor;
};


class SurroundedRegions
{
public:
	SurroundedRegions() {}
	~SurroundedRegions() {}
	// load the matrix from a file 
	void	loadMatrix(string fileName);
	void	printMatrix();
	
	void	convert();
	void	convert2();
	
	Node&	getNode(int i, int j);
	
private:	
	vector<string> 		split(const string &s, char delim);
	vector<string>&		split(const string &s, char delim, vector<string> &elems);
	
	bool				processNode(int i, int j, stack<pair<int, int> >& nodePositionStack);
	bool				processNode2(int i, int j, stack<pair<int, int> >& nodePositionStack);
	
	bool				positionOutOfMatrix(int i, int j);
	
private:
	vector<vector<Node> >			m_vMatrix;
};


void SurroundedRegions::loadMatrix(string fileName)
{
	m_vMatrix.clear();
	ifstream myfile (fileName.c_str());
	if (!myfile.is_open())
	{
		cout << "Unable to open file"; 
		exit(0);
	}
	
	int n = -1;
	
	while (myfile.good())
	{
		string line;
		getline (myfile,line);
		
		vector<string> items = split(line, ' ');
		if(items.size() <= 0)
			break;
		
		vector<Node> itemLine;
		for(int i=0; i<items.size(); i++)
		{
			string item = items[i];
			// ifastream<basic_formatters, string_reader> myString(&item);
			// int value;
			// myString >> value;
			
			char cvalue = item[0];
			if(cvalue=='X' || cvalue=='O')
			{
				Node node(item[0]);
				itemLine.push_back(node);
			}
		}
		m_vMatrix.push_back(itemLine);
	}
	myfile.close();
}


vector<string> &SurroundedRegions::split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim))
	{
		if(item.size() > 0)
			elems.push_back(item);
    }
    return elems;
}

vector<string> SurroundedRegions::split(const string &s, char delim)
 {
    vector<string> elems;
    return split(s, delim, elems);
}

void SurroundedRegions::printMatrix()
{
	for(int i=0; i<m_vMatrix.size(); i++)
	{
		for(int j=0; j<m_vMatrix[i].size(); j++)
			cout << " " << m_vMatrix[i][j].getCharValue();
		cout << endl;
	}
	cout << endl << endl;
}


Node& SurroundedRegions::getNode(int i, int j)
{
	if(i < 0)
		throw "error: row overflow";
		
	if(j < 0)
		throw "error: column overflow";
		
	int m = m_vMatrix.size();
	if(i >= m)
		throw "error: row overflow";
		
	vector<Node> &nodeLine = m_vMatrix[i];
	int n = nodeLine.size();
	if(j >= n)
		throw "error: column overflow";
	
	return nodeLine[j];
}


bool SurroundedRegions::positionOutOfMatrix(int i, int j)
{
	if(i < 0)
		return true;
	int m = m_vMatrix.size();
	if(i >= m)
		return true;

	if(j < 0)
		return true;
	
	vector<Node> &nodeLine = m_vMatrix[i];
	int n = nodeLine.size();
	if(j >= n)
		return true;

	return false;
}


/*
	1. For each O char, we search for its four directions, if it there is a O adjecent, push the old O into stack and deep first to the new O.
		If there is one O that is on the edge, then this group are not surrounded by X. When there is no O can be found, then mark the whole group as visited.
		If there is no O that is on the edge, then this group are surrounded by X. When there is no O can be found, flip the char and make the whole group as visited
*/
void SurroundedRegions::convert()
{
	int m = m_vMatrix.size();
	for(int i=0; i<m; i++)
	{
		vector<Node> &nodeLine = m_vMatrix[i];
		int n = nodeLine.size();
		for(int j=0; j<n; j++)
		{
			Node &node = nodeLine[j];
			if(!node.isVisited() && node.isBigO())
			{
				stack<pair<int, int> > nodePositionStack;
				bool bSurrounded = processNode(i, j, nodePositionStack);
				if(bSurrounded)
				{
					// change all O to X
					while(!nodePositionStack.empty())
					{
						pair<int, int>& pos = nodePositionStack.top();
						int x = pos.first;
						int y = pos.second;
						
						Node& node = getNode(x, y);
						node.setCharValue('X');
						nodePositionStack.pop();
					}
				}
			}
		}
	}
}

void SurroundedRegions::convert2()
{
	int m = m_vMatrix.size();
	for(int i=0; i<m; i++)
	{
		vector<Node> &nodeLine = m_vMatrix[i];
		int n = nodeLine.size();
		for(int j=0; j<n; j++)
		{
			Node &node = nodeLine[j];
			if(!node.isVisited() && node.isBigO())
			{
				stack<pair<int, int> > nodePositionStack;
				bool bSurrounded = processNode2(i, j, nodePositionStack);
				if(bSurrounded)
				{
					// change all O to X
					while(!nodePositionStack.empty())
					{
						pair<int, int>& pos = nodePositionStack.top();
						int x = pos.first;
						int y = pos.second;
						
						Node& node = getNode(x, y);
						node.setCharValue('X');
						nodePositionStack.pop();
					}
				}
			}
		}
	}
}


/*
	process from node [i,j] until all connected node are visited.
	return true if it is surrounded by Xs, return false if not.
	When come here, we are sure the node (i, j) is 'O' and not visited yet
 */
bool SurroundedRegions::processNode(int i, int j, stack<pair<int, int> >& nodePositionStack)
{
	int m = m_vMatrix.size();
	if(i<0 || i>=m)
		return false;
		
	vector<Node> &nodeLine = m_vMatrix[i];
	int n = nodeLine.size();
	if(j<0 || j>=n)
		return false;
	
	Node& node = getNode(i, j);
	
	if(!node.isBigO())
		return true;
	
	if(node.isVisited())
		return true;

	// Now it is a valid node
	node.setNodeColor(E_COLOR_GREY); // this node is visited
	pair<int, int> posPair = make_pair(i, j); // push the position to stack
	nodePositionStack.push(posPair);
	
	// go up
	bool bSurroundedUp = processNode(i-1, j, nodePositionStack);
	
	// go down
	bool bSurroundedDown = processNode(i+1, j, nodePositionStack);

	// go left
	bool bSurroundedLeft = processNode(i, j-1, nodePositionStack);
	
	// go right
	bool bSurroundedRight = processNode(i, j+1, nodePositionStack);


	bool bSurrounded = bSurroundedUp && bSurroundedDown && bSurroundedLeft && bSurroundedRight;
	
	return bSurrounded;
}


/*
	implement processNode() without using recursion
 */
bool SurroundedRegions::processNode2(int i, int j, stack<pair<int, int> >& nodePositionStack)
{
	bool bSurrounded = true;
	stack<pair<int, int> > stackLocal;
	
	// add seed element
	Node& node = getNode(i, j);
	node.setNodeColor(E_COLOR_GREY); // this node is visited
	pair<int, int> pos = make_pair(i, j);
	stackLocal.push(pos);
	nodePositionStack.push(pos);
	
	while(!stackLocal.empty())
	{
		bool bOutOfRange = false;
		pair<int, int> pos = stackLocal.top();
		stackLocal.pop();
		
		int i = pos.first;
		int j = pos.second;
		
		if(positionOutOfMatrix(i, j))
		{
			bSurrounded = false;
			continue;
		}
		
		Node &node = getNode(i, j);

		if(!node.isBigO())
			continue;

		// up direction
		pos = make_pair(i-1, j);
		if(positionOutOfMatrix(pos.first, pos.second))
		{
			bSurrounded = false;
		}
		else
		{
			Node &node = getNode(pos.first, pos.second);
			if(node.isBigO() && !node.isVisited())
			{
				node.setNodeColor(E_COLOR_GREY); // this node is visited
				stackLocal.push(pos);
				nodePositionStack.push(pos);
			}
		}
		
		
		// down direction
		pos = make_pair(i+1, j);
		if(positionOutOfMatrix(pos.first, pos.second))
		{
			bSurrounded = false;
		}
		else
		{
			Node &node = getNode(pos.first, pos.second);
			if(node.isBigO() && !node.isVisited())
			{
				node.setNodeColor(E_COLOR_GREY); // this node is visited
				stackLocal.push(pos);
				nodePositionStack.push(pos);
			}
		}

		// left direction
		pos = make_pair(i, j-1);
		if(positionOutOfMatrix(pos.first, pos.second))
		{
			bSurrounded = false;
		}
		else
		{
			Node &node = getNode(pos.first, pos.second);
			if(node.isBigO() && !node.isVisited())
			{
				node.setNodeColor(E_COLOR_GREY); // this node is visited
				stackLocal.push(pos);
				nodePositionStack.push(pos);
			}
		}
		
		// right direction
		pos = make_pair(i, j+1);
		if(positionOutOfMatrix(pos.first, pos.second))
		{
			bSurrounded = false;
		}
		else
		{
			Node &node = getNode(pos.first, pos.second);
			if(node.isBigO() && !node.isVisited())
			{
				node.setNodeColor(E_COLOR_GREY); // this node is visited
				stackLocal.push(pos);
				nodePositionStack.push(pos);
			}
		}
	}
	
	return bSurrounded;
}

int main(int argc, char **argv)
{
	cout << "case 1:" << endl;
	SurroundedRegions parser;
	parser.loadMatrix("test.input");
	parser.printMatrix();
	parser.convert();
	parser.printMatrix();

	cout << "case 2:" << endl;
	parser.loadMatrix("test.input");
	parser.printMatrix();
	parser.convert2();
	parser.printMatrix();
	
	cout << "case 3:" << endl;
	parser.loadMatrix("test.input2");
	parser.printMatrix();
	parser.convert();
	parser.printMatrix();

	cout << "case 4:" << endl;
	parser.loadMatrix("test.input2");
	parser.printMatrix();
	parser.convert2();
	parser.printMatrix();
}



