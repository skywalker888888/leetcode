#include <string>
#include <iostream>
#include <vector>
using namespace std;

/**
	http://leetcode.com/onlinejudge
	2. Palindrome Partitioning
		Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
		For example, given s = "aab", Return
		  [
			["aa","b"],
			["a","a","b"]
		  ]
 */
// pass 3
// Time: O(
class Solution {
public:
    vector<vector<string> > partition(string s) {
    	int n = s.size();
		if(!n)
			return vector<vector<string> >();
			
		vector<vector<bool> > M(n, vector<bool>(n, false));
		for(int len=0; len<n; ++len)
			for(int i=0; i<n-len; ++i) {
				int j = i + len;
				if(!len)
					M[i][j] = true;
				else if(s[i]==s[j] && (i+1==j || M[i+1][j-1]))
					M[i][j] = true;
				else
					M[i][j] = false;
			}
	
		vector<vector<string> > result;
		
		vector<pair<int, int> > vtrPos;
		vtrPos.push_back(pair<int, int>(0, 0));
		while(vtrPos.size()) {
			pair<int, int> last = vtrPos[vtrPos.size()-1];
			int st = last.first;
			int ed = last.second;
			if(ed == n-1) {
				vector<string> item;
				for(int i=0; i<vtrPos.size(); ++i)
					item.push_back(s.substr(vtrPos[i].first, vtrPos[i].second-vtrPos[i].first+1)); // s[vtrPos[i].first .. vtrPos[i].second]
				result.push_back(item);
				bool finished = false;
				while(!finished && vtrPos.size()) {
					// pop the last item
					vtrPos.pop_back();
					// increase the last item
					if(!vtrPos.size())
						break;
					for(int k=vtrPos[vtrPos.size()-1].second+1; k<n; ++k)
						if(M[vtrPos[vtrPos.size()-1].first][k]) {
							vtrPos[vtrPos.size()-1].second = k;
							finished = true;
							break;
						}
				}
			} else {
				// 
				vtrPos.push_back(pair<int, int>(ed+1, ed+1));
			}
		}
		
		return result;
    }
};































/*
	Analyse:
		A NULL string is a palindrome
		If S[i]==S[j] && S[i+1..j-1] is a palindrome, then S[i..j] is a palindrome
		Make a matrix bool C{i][j] to mark S[i..j] is a palindrome or not
	
	Solution:
		Recursively print out
*/
class Solution {
public:
	vector<vector<string> > partition(string s)
	{
		int n = s.size();
		vector<vector<string> > result;
		if(!n)
			return result;
			
		vector<vector<bool> > P(n, vector<bool>(n, false));
		for(int len = 0; len<n; ++len)
			for(int i=0; i<n-len; ++i)
			{
				int j = i + len;
				if(i == j)
					P[i][j] = true;
				else if(i+1 == j)
					if(s[i] == s[j])
						P[i][j] = true;
					else 
						P[i][j] = false;
				else if(s[i] == s[j])
					P[i][j] = P[i+1][j-1];
				else
					P[i][j] = false;
			}
		
		vector<string> item;
		generateResult(s, P, 0, result, item);
		return result;
	}
	void generateResult(string& s, vector<vector<bool> >& P, int index, vector<vector<string> > &result, vector<string> item)
	{
		int n = s.size();
		if(index == n)
		{
			result.push_back(item);
			return;
		}
		for(int i=index; i<n; ++i)
		{
			if(P[index][i])
			{
				vector<string> item2 = item;
				item2.push_back(s.substr(index, i-index+1));
				generateResult(s, P, i+1, result, item2);
			}
		}
	}
};




















vector<vector<string> > Solution::partition(string s)
{
	int n = s.size();
	vector<vector<string> > result;
	if(!n)
		return result;
		
	vector<vector<bool> > P(n, vector<bool>(n, false));
	for(int len = 0; len<n; ++len)
		for(int i=0; i<n-len; ++i)
		{
			int j = i + len;
			if(i == j)
				P[i][j] = true;
			else if(i+1 == j)
				if(s[i] == s[j])
					P[i][j] = true;
				else 
					P[i][j] = false;
			else if(s[i] == s[j])
				P[i][j] = P[i+1][j-1];
			else
				P[i][j] = false;
		}
	
	// DFS 
	vector<int> inds(n, 0);
	int index = 0;
	inds[0] = 0;
	while(inds[0] < n)
	{
		int nextindex = inds[index]+1;
		bool bRetreat = true;
		if(nextindex < n)
		{
			++index;
			inds[index] = nextindex;
			bRetreat = false;
		}
		
		while(inds[index]==n-1 || bRetreat)
		{
			if(inds[index] == n-1)
				addLineToResult(s, inds, index, result);
			bRetreat = true;
			--index;
			int nOrg = 0;
			if(index > 0)
				nOrg = inds[index-1];
			else nOrg = 0;
			
			for(int i=inds[index]+1; i<n; ++i)
				if(P[nOrg][i])
				{
					bRetreat = false;
					++index;
					inds[index] = i;
					break;
				}
			if(!index && bRetreat)
			{
				inds[0] = n;
				break;
			}
		}
	}
	
	return result;
}


void Solution::addLineToResult(string &s, vector<int> &inds, int index, vector<vector<string> >& result)
{
	vector<string> item;
	for(int i=0; i<=index; ++i)
	{
		if(!i)
			item.push_back(s.substr(0, i));
		else
			item.push_back(s.substr(inds[i-1]+1, inds[i]-inds[i-1]));
	}
	
	result.push_back(item);
}


						
 
class PalindromePartitioning
{
	static const int	MATRIX_VALUE_NOT_INIT;
	static const int	MATRIX_VALUE_TRUE;
	static const int	MATRIX_VALUE_FALSE;
	
public:
	PalindromePartitioning(){}
	~PalindromePartitioning(){}
	void	setString(const string& input);

	void	memoizedParse();
	void	directParse();

	void	printPalindrome();
	
private:
	int		memoizedParse(int i, int j);
	void	resetMatrixState();
	
	void	initMarkMatrix();

	void	printPalindrome(int i, int j, const vector<string>& content);
	void	printStringList(const vector<string>& palis);
	
private:
	string					m_strData;
	vector<vector<int> >	C;
};

const int PalindromePartitioning::MATRIX_VALUE_NOT_INIT = -1;
const int PalindromePartitioning::MATRIX_VALUE_TRUE = 1;
const int PalindromePartitioning::MATRIX_VALUE_FALSE = 0;


/*
	set a string to parse. 
	When a  new string is used, the mark matrix will be initialized 
 */
void PalindromePartitioning::setString(const string& input)
{
	m_strData = input;
	C.clear();
	int n = m_strData.size();
	for(int i=0; i<n; i++)
	{
		vector<int> line;
		for(int j=0; j<n; j++)
		{
			line.push_back(MATRIX_VALUE_NOT_INIT);
		}
		
		C.push_back(line);
	}
}


void PalindromePartitioning::resetMatrixState()
{
	int n = m_strData.size();
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			C[i][j] = MATRIX_VALUE_NOT_INIT;
}


void PalindromePartitioning::memoizedParse()
{
	int n = m_strData.size();
	resetMatrixState();
	
	memoizedParse(0, n-1);
}


/*
	parse string S[i..j] and mark the C[i][j] to indicate if S[i..j] is a palindrome
	If S[i..j] is NULL, return true
	If C[i][j] has value already, 
 */
int PalindromePartitioning::memoizedParse(int i, int j)
{
	if(i > j)
		return MATRIX_VALUE_TRUE;
		
	if(C[i][j] != MATRIX_VALUE_NOT_INIT)
		return C[i][j];

	memoizedParse(i+1, j);
	memoizedParse(i, j-1);
	if(m_strData[i] != m_strData[j])
	{
		C[i][j] = MATRIX_VALUE_FALSE;
	}
	else
	{
		C[i][j] = memoizedParse(i+1, j-1);
	}
	return C[i][j];
}

/*
	print the palindrome
 */
void PalindromePartitioning::printPalindrome()
{
	cout << "print palindrome of string: " << m_strData << endl;
	int n = m_strData.size();
	vector<string> content;
	cout << "[" << endl;
	printPalindrome(0, n-1, content);
	cout << "]" << endl << endl;
}


void PalindromePartitioning::printPalindrome(int i, int j, const vector<string>& content)
{
	if(i > j)
	{
		printStringList(content);
		return;
	}
	
	// compute
	for(int k=i; k<=j; k++)
	{
		if(C[i][k] == MATRIX_VALUE_TRUE)
		{
			string sik = m_strData.substr(i, k-i+1);
			vector<string> newContent = content; 
			newContent.push_back(sik);
			printPalindrome(k+1, j, newContent);
		}
	}
}


/*
	print a string list as: \t["str", "str", "str", "str", "str"]
 */
void PalindromePartitioning::printStringList(const vector<string>& palis)
{
	cout << "\t";
	for(int i=0; i<palis.size(); i++)
	{
		if(i)
			cout << ", ";
		cout << "\"";
		cout << palis[i];
		cout << "\"";
	}
	cout << endl;
}


