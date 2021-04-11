/*
	Given a string s, partition s such that every substring of the partition is a palindrome.

	Return the minimum cuts needed for a palindrome partitioning of s.

	For example, given s = "aab",
	Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/
// pass 3
// Time: O(n^2)
// Space: O(n^2)
class Solution {
public:
    int minCut(string s) {
    	int n = s.size();
		if(!n)
			return 0;
		
		/*
			M[i][j] =	true if i==j
						true if s[i]==s[j] && (i+1==j || M[i+1][j-1]==0)
						false, others
		*/
		vector<vector<bool> > M(n, vector<bool>(n, false));
		for(int len=0; len<n; ++len)
			for(int i=0; i<n-len; ++i) {
				int j = i + len;
				if(!len)
					M[i][j] = true;
				else if(s[i]==s[j] &&(len==1 || M[i+1][j-1]))
					M[i][j] = true;
			}
		
		// for each i, find the min cut of s[0...i]
		vector<int> minCut(n, 0);
		for(int i=0; i<n; ++i)
			if(M[0][i])
				minCut[i] = 0;
			else {
				// should be no more than i cuts for i+1 items
				int minVal = i+1;
				for(int k=0; k<i; ++k)
					if(M[k+1][i])
						minVal = min(minVal, minCut[k]+1);
				minCut[i] = minVal;
			}
				
		return minCut[n-1];
	}
};

// Time: O(n^3)
// Space: O(n^2)
class Solution {
public:
    int minCut(string s) {
		int n = s.size();
		if(!n)
			return 0;
		
		/*
			M[i][j] =	0 if i==j
						0 if s[i]==s[j] && (i+1==j || M[i+1][j-1]==0)
						min(M[i+1][j], M[i][j-1]) + 1, others
		*/
		vector<vector<int> > M(n, vector<int>(n, 0));
		for(int len=0; len<n; ++len)
			for(int i=0; i<n-len; ++i) {
				int j = i + len;
				if(!len)
					M[i][j] = 0;
				else if(s[i]==s[j] && (len==1 || !M[i+1][j-1]))
					M[i][j] = 0;
				else {
					int minVal = M[i+1][j];
					for(int m=i; m<j; ++m)
							minVal = min(minVal, M[i][m]+M[m+1][j]);
					M[i][j] = minVal + 1;
				}
			}
		return M[0][n-1];
    }
};




































#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
	http://leetcode.com/onlinejudge
	
	Palindrome Partitioning II
		Given a string s, partition s such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s. 
		For example, given s = "aab", Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
		
	Analysis:
		In order for the cut be minimum, the palindrome segments should be maximum. Prove with cut and paste.
		let C[i,j] be the minimum cut of string S[i..j]
		let D[i,j] be the cut position of C[i..j]
		we have, for all i<=j
		C[i,j]=0 and D[i,j]=-1 if i==j // a
		C[i,j]=0 and D[i,j]=-1 if i+1==j and S[i]==S[j]
		C[i,j]=1 and D[i,j]=i if i+1==j and S[i]!=S[j]
		C[i,j]=0 and D[i,j]=-1 if S[i]==S[j] and C[i+1,j-1]==0
		C[i,j]=min{C[i,m]+C[m+1,j]+1}, for others
		
	Solution:
		C[1,n]
	
*/



class Solution {
public:
    int minCut(string s);
};

int Solution::minCut(string s)
{
	int n = s.size();
	if(n < 2)
		return 0;

	// 
	vector<vector<bool> > matrix(n, vector<bool>(n, false));
	for(int len=0; len<n; ++len)
		for(int i=0; i<n-len; ++i)
		{
			int j = i + len;
			if(i == j)
				matrix[i][j] = true;
			else if(i+1 == j)
			{
				if(s[i] == s[j])
					matrix[i][j] = true;
				else
					matrix[i][j] = false;
			}
			else if(s[i]==s[j] && matrix[i+1][j-1])
				matrix[i][j] = true;
			else
				matrix[i][j] = false;
		}
	
	// define minCutTillEnd[i] as the mincut value from i to n-1
	// so we can solve the problem in O(n^2) time
	vector<int> minCutTillEnd(n);
	for(int i=n-1; i>=0; --i)
	{
		if(matrix[i][n-1])
			minCutTillEnd[i] = 0;
		else
		{
			int mincut = minCutTillEnd[i+1]+1;
			for(int k=i; k<n-1; ++k)
				if(matrix[i][k])
					mincut = min(mincut, minCutTillEnd[k+1]+1);
			minCutTillEnd[i] = mincut;
		}
	}
	return minCutTillEnd[0];
}

class Solution {
public:
    int minCut(string s);
    int minCut2(string s);
	
private:
	int	minCutSub(vector<vector<int> >& matrix, int i, int j, string& s);
};

int Solution::minCut(string s)
{
	int n = s.size();
	if(n <= 1)
		return 0;
	if(n == 2)
		if(s[0] == s[1])
			return 0;
		else 
			return 1;
	
	vector<vector<int> > matrix(n, vector<int>(n, -1));
	
	for(int i=0; i<n; ++i)
		matrix[i][i] = 0;
	for(int i=0; i<n-1; ++i)
		matrix[i][i+1] = s[i]==s[i+1]?0:1;
	
	for(int nLen = 2; nLen<n; ++nLen)
		for(int i=0; i<n-nLen; ++i)
		{
			int j = i+nLen;
			if(s[i]==s[j] && !matrix[i+1][j-1])
				matrix[i][j] = 0;
			else
			{
				int nMin;
				for(int m=i; m<j; ++m)
				{
					int res = matrix[i][m] + matrix[m+1][j] + 1;
					if(m == i)
						nMin = res;
					else
						nMin = min(nMin, res);
				}
				matrix[i][j] = nMin;
			}
		}
	return matrix[0][n-1];
}


int main(int argc, char **argv)
{
        int n = 12;
        string s = "apjesgpsxoeiokmqmfgvjslcjukbqxpsobyhjpbgdfruqdkeiszrlmtwgfxyfostpqczidfljwfbbrflkgdvtytbgqalguewnhvvmcgxboycffopmtmhtfizxkmeftcucxpobxmelmjtuzigsxnncxpaibgpuijwhankxbplpyejxmrrjgeoevqozwdtgospohznkoyzocjlracchjqnggbfeebmuvbicbvmpuleywrpzwsihivnrwtxcukwplgtobhgxukwrdlszfaiqxwjvrgxnsveedxseeyeykarqnjrtlaliyudpacctzizcftjlunlgnfwcqqxcqikocqffsjyurzwysfjmswvhbrmshjuzsgpwyubtfbnwajuvrfhlccvfwhxfqthkcwhatktymgxostjlztwdxritygbrbibdgkezvzajizxasjnrcjwzdfvdnwwqeyumkamhzoqhnqjfzwzbixclcxqrtniznemxeahfozp";

        Solution sol;
        int num = sol.minCut(s);

        cout << "num: " << num << "\n";
}


int Solution::minCut2(string s)
{
	int n = s.size();
	if(n <= 1)
		return 0;
	if(n == 2)
		if(s[0] == s[1])
			return 0;
		else 
			return 1;
	
	vector<vector<int> > matrix(n, vector<int>(n, -1));
	
	int res = minCut(matrix, 0, n-1, s);
	return res;
	
}

int	Solution::minCutSub(vector<vector<int> >& matrix, int i, int j, string& s)
{
	if(matrix[i][j] >= 0)
		return matrix[i][j];
		
	if(j == i)
	{
		matrix[i][j] = 0;
		return matrix[i][j];
	}
	else if(i+1 == j)
		if(s[i]==s[j])
		{
			matrix[i][j] = 0;
			return matrix[i][j];
		}
		else
		{
			matrix[i][j] = 1;
			return matrix[i][j];
		}
	else
	{
		int nMin;
		bool bHasMin = false;
		if(s[i]==s[j] &&!minCutSub(matrix, i+1, j-1, s))
		{
			bHasMin = true;
			nMin = 0;
		}
		
		for(int m=i; m<j; ++m)
		{
			int res = minCutSub(matrix, i, m, s) + minCutSub(matrix, m+1, j, s) + 1;
			if(bHasMin)
				nMin = min(nMin, res);
			else
			{
				nMin = res;
				bHasMin = true;
			}
		}
		
		matrix[i][j] = nMin;
		return nMin;
	}
}



class CPalindromePartitioningII
{
	static const int LEN_INFI; // maximum cut value
	static const int NUL_POS; // the NULL cut position
public:
	CPalindromePartitioningII(){}
	~CPalindromePartitioningII() {}
	void	setString(const string& input);
	void	memoizedParseInput();
	void	memoizedParseInput2();
	void	directParseInput();
	void	directParseInput2();
	
	void	memoizedPrintResult();
	void	memoizedPrintResult2();
	void	directPrintResult();
	
	string	generateRandomString(int n);

private:
	void	initState();
	void	memoizedCalculate(int i, int j);
	void	memoizedCalculate2(int i, int j);
	
	void	printResult(int i, int j);

private:
	string m_strInput;
	vector<vector<int> > C;
	vector<vector<int> > D;
};


const int CPalindromePartitioningII::LEN_INFI = 99999; // maximum cut value
const int CPalindromePartitioningII::NUL_POS = -1; // the NULL cut position


void CPalindromePartitioningII::setString(const string& input)
{
	m_strInput = input;
}


/*
		In order for the cut be minimum, the palindrome segments should be maximum. Prove with cut and paste.
		let C[i,j] be the minimum cut of string S[i..j]
		let D[i,j] be the cut position of C[i..j]
		we have, for all i<=j
		C[i,j]=0 and D[i,j]=-1 if i==j // a
		C[i,j]=0 and D[i,j]=-1 if i+1==j and S[i]==S[j]
		C[i,j]=1 and D[i,j]=i if i+1==j and S[i]!=S[j]
		C[i,j]=0 and D[i,j]=-1 if S[i]==S[j] and C[i+1,j-1]==0
		C[i,j]=min{C[i,m]+C[m+1,j]+1}, for others
 */
void CPalindromePartitioningII::memoizedParseInput()
{
	initState();
	memoizedCalculate(0, m_strInput.size()-1);
}


/*
	Calculate C[i][j] and D[i][j]
	1. NULL string(i>j) is a palindrome by default, nothing need to be done
 */
void CPalindromePartitioningII::memoizedParseInput2()
{
	initState();
	memoizedCalculate2(0, m_strInput.size()-1);
}

void CPalindromePartitioningII::memoizedCalculate2(int i, int j)
{
	if(i > j)
		return;
	
	if(C[i][j] != LEN_INFI)
		return; 
	
	if(i == j)
	{
		C[i][j] = 0;
		D[i][j] = NUL_POS;
	}
	else if(i+1 == j)
	{
		if(m_strInput[i]==m_strInput[j])
		{
			C[i][j] = 0;
			D[i][j] = NUL_POS;
		}
		else
		{
			C[i][j] = 1;
			D[i][j] = i;
		}
	}
	else // i<j
	{
		int nMinCutNum = LEN_INFI;
		int nCutPos = NUL_POS;
		
		for(int k=i; k<j; k++)
		{
			memoizedCalculate2(i, k);
			memoizedCalculate2(k+1, j);
			if(nMinCutNum > C[i][k] + C[k+1][j] + 1)
			{
				nMinCutNum = C[i][k] + C[k+1][j] + 1;
				nCutPos = k;
			}
		}
		
		if(m_strInput[i]==m_strInput[j] && C[i+1][j-1]==0)
		{
			C[i][j] = 0;
			D[i][j] = NUL_POS;
		}
		else
		{
			C[i][j] = nMinCutNum;
			D[i][j] = nCutPos;
		}
	}
}


void CPalindromePartitioningII::directParseInput()
{
	initState();
	
	int nStart = 0;
	int nEnd  = m_strInput.size()-1;
	// 
	for(int i=0; i<=nEnd; i++)
	{
		C[i][i] = 0;
		D[i][i] = NUL_POS;
	}
	
	for(int nLen=1; nLen<=nEnd; nLen++)
	{
		for(int i=0; i<=nEnd; i++)
		{
			int j = i + nLen;
			if(j>nEnd)
				break;
			
			if(j==i+1)
			{
				if(m_strInput[i]==m_strInput[j])
				{
					C[i][j] = 0;
					D[i][j] = NUL_POS;
				}
				else
				{
					C[i][j] = 1;
					D[i][j] = i;
				}
			}
			else if(j>i+1 && m_strInput[i]==m_strInput[j] && C[i+1][j-1]==0)
			{
				C[i][j] = 0;
				D[i][j] = NUL_POS;
			}
			else
			{
				int nMinCutNum = LEN_INFI;
				int nCutPos = NUL_POS;
				for(int m=i; m<j; m++)
				{
					if(nMinCutNum > C[i][m]+C[m+1][j]+1)
					{
						nMinCutNum = C[i][m]+C[m+1][j]+1;
						nCutPos = m;
					}
				}
				
				C[i][j] = nMinCutNum;
				D[i][j] = nCutPos;
			}
		}
	}
}

// No idea yet
void CPalindromePartitioningII::directParseInput2()
{
	initState();
	
	int nStart = 0;
	int nEnd  = m_strInput.size()-1;
	for(int i=0; i<=nEnd; i++)
	{
		C[i][i] = 0;
		D[i][i] = NUL_POS;
	}

	for(int i=0; i<=nEnd; i++)
	{
		//??????
	}
}

void CPalindromePartitioningII::memoizedPrintResult()
{
	int nStart = 0;
	int nEnd = m_strInput.size()-1;
	cout << "the string pased: " << m_strInput << endl;
	cout << "memoized parsing minimum cut number is:" << C[nStart][nEnd] << endl;
	cout << "the memoized parsing palindrome list: " << endl;
	printResult(nStart, nEnd);
	
	cout << endl << endl;
}


void CPalindromePartitioningII::memoizedPrintResult2()
{
	int nStart = 0;
	int nEnd = m_strInput.size()-1;
	cout << "the string pased: " << m_strInput << endl;
	cout << "memoized2 parsing minimum cut number is:" << C[nStart][nEnd] << endl;
	cout << "the memoized2 parsing palindrome list: " << endl;
	printResult(nStart, nEnd);
	
	cout << endl << endl;
}


void CPalindromePartitioningII::directPrintResult()
{
	int nStart = 0;
	int nEnd = m_strInput.size()-1;
	cout << "the string pased: " << m_strInput << endl;
	cout << "direct parsing minimum cut number is:" << C[nStart][nEnd] << endl;
	cout << "the direct parsing palindrome list: " << endl;
	printResult(nStart, nEnd);
	
	cout << endl << endl;
}


void CPalindromePartitioningII::printResult(int i, int j)
{
	if(i>j)
		return;
	
	if(C[i][j] == 0)
	{
		cout << "position(" << i << "," << j <<"): " << m_strInput.substr (i, j-i+1) << endl;
	}
	else
	{
		int k = D[i][j];
		printResult(i, k);
		printResult(k+1, j);
	}
}

void CPalindromePartitioningII::initState()
{
	C.clear();
	D.clear();
	
	// construct matrix C[n*n] and D[n*n]
	int n = m_strInput.size(); // or m_strInput.length();
	for(int i=0; i<n; i++)
	{
		vector<int> CC;
		vector<int> DD;
		for(int j=0; j<n; j++)
		{
			CC.push_back(LEN_INFI);
			DD.push_back(NUL_POS);
		}
		C.push_back(CC);
		D.push_back(DD);
	}
}

/**
	we have, for all i<=j
	C[i,j]=0 and D[i,j]=-1 if i==j // a
	C[i,j]=0 and D[i,j]=-1 if i+1==j and S[i]==S[j]
	C[i,j]=1 and D[i,j]=i if i+1==j and S[i]!=S[j]
	C[i,j]=0 and D[i,j]=-1 if S[i]==S[j] and C[i+1,j-1]==0
	C[i,j]=min{C[i,m]+C[m+1,j]+1}, for others
 */
void CPalindromePartitioningII::memoizedCalculate(int i, int j)
{
	if(i>j)
		return;

	if(C[i][j] < LEN_INFI)
		return;
		
	// j == i
	if(i == j)
	{
		C[i][j] = 0;
		D[i][j] = NUL_POS;
		return;
	}

	// j == i+1
	if(i+1 == j)
	{
		if(m_strInput[i] == m_strInput[j])
		{
			C[i][j] = 0;
			D[i][j] = NUL_POS;
		}
		else
		{
			C[i][j] = 1;
			D[i][j] = i; // means the cut is between i and i+1
		}
		return;
	}

	// now j > i+1
	if(m_strInput[i] == m_strInput[j])
	{
		memoizedCalculate(i+1, j-1);
		if(C[i+1][j-1] == 0)
		{
			C[i][j] = 0;
			D[i][j] = NUL_POS;
			return;
		}
	}
	
	// C[i,j]=min{C[i,m]+C[m+1,j]+1}, for others
	int nLen = LEN_INFI;
	int nPartitionPos = NUL_POS;
	for(int m=i; m<j; m++)
	{
		memoizedCalculate(i, m);
		memoizedCalculate(m+1, j);
		if(nLen > C[i][m]+C[m+1][j]+1)
		{
			nLen = C[i][m]+C[m+1][j]+1;
			nPartitionPos = m;
		}
	}
	C[i][j] = nLen;
	D[i][j] = nPartitionPos;
}


string CPalindromePartitioningII::generateRandomString(int n)
{
	string result;
	for(int i=0; i<n; i++)
	{
		int val = random() % 26;
		int nVal = 'a' +  val;
		char cVal = (char)nVal;
		result += cVal;
	}
	
	return result;
}



int main(int argc, char **argv)
{
	CPalindromePartitioningII parser;
	
	string inputStr; 
	
	parser.setString("nwlrbbmqbh");
	parser.memoizedParseInput();
	parser.memoizedPrintResult();
	parser.memoizedParseInput2();
	parser.memoizedPrintResult2();
	parser.directParseInput();
	parser.directPrintResult();
	
	inputStr = parser.generateRandomString(10);
	parser.setString(inputStr);
	parser.memoizedParseInput();
	parser.memoizedPrintResult();
	parser.memoizedParseInput2();
	parser.memoizedPrintResult2();
	parser.directParseInput();
	parser.directPrintResult();

	inputStr = parser.generateRandomString(20);
	parser.setString(inputStr);
	parser.memoizedParseInput();
	parser.memoizedPrintResult();
	parser.memoizedParseInput2();
	parser.memoizedPrintResult2();
	parser.directParseInput();
	parser.directPrintResult();

	inputStr = parser.generateRandomString(30);
	parser.setString(inputStr);
	parser.memoizedParseInput();
	parser.memoizedPrintResult();
	parser.memoizedParseInput2();
	parser.memoizedPrintResult2();
	parser.directParseInput();
	parser.directPrintResult();

	parser.setString("aaabbaaaaa");
	parser.memoizedParseInput();
	parser.memoizedPrintResult();
	parser.memoizedParseInput2();
	parser.memoizedPrintResult2();
	parser.directParseInput();
	parser.directPrintResult();

	parser.setString("abcabccbaabccba");
	parser.memoizedParseInput();
	parser.memoizedPrintResult();
	parser.memoizedParseInput2();
	parser.memoizedPrintResult2();
	parser.directParseInput();
	parser.directPrintResult();

	parser.setString("abccbaefggfeacdddcaadfdfddd");
	parser.memoizedParseInput();
	parser.memoizedPrintResult();
	parser.memoizedParseInput2();
	parser.memoizedPrintResult2();
	parser.directParseInput();
	parser.directPrintResult();
	
}

