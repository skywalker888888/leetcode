#include <string>
#include <vector>
#include <vector>
using namespace std;

/**
		Given a string S and a string T, count the number of distinct subsequences of T in S.

		A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

		Here is an example:
		S = "rabbbit", T = "rabbit"

		Return 3.
		
					
*/
// pass 3
class Solution {
public:
    int numDistinct(string S, string T) {
		int m = S.size();
		int n = T.size();
		if(!m)
			return m;
		if(!n)
			return 1;
		/*
			M[i][j]: look for T[0...j-1] in S[0....i]
			M[i][j] = 	1, if j=0, when T[0..j-1] is NULL 
						0, if i<j, when T[] is shorter than S[]
						M[i-1][j], if T[j-1] != S[i]
						M[i-1][j-1] + M[i-1][j], if T[j-1] == S[i]
						
		*/
		vector<vector<int> > M(2, vector<int>(n+1, 0));
		
		M[0][0] = 1;
		int flag = 1;
		for(int i=0; i<m; ++i) {
			M[flag][0] = 1;
			for(int j=1; j<=n; ++j) {
				if(j > i+1)
					M[flag][j] = 0;
				else if(T[j-1] != S[i])
					M[flag][j] = M[!flag][j];
				else
					M[flag][j] = M[!flag][j-1] + M[!flag][j];
			}
			flag = !flag;
		}
		
		return M[!flag][n];
    }
};







































/*
		Analysis:
			This question is asking how many S's distinct subsequences are exactly T. 
			We define M[i, j] as the problem for S[0...i] and T[0..j]. We have 
			M[i,j]	= 1 if j<0
					= 0 if i<j
					= M[i-1, j-1] + M[i-1, j], if S[i]==T[j]
					= M[i-1, j], if S[i]!=T[j]
*/
 
////////////// pass 2
// Time: O(m * n)
// Space: O(n)
class Solution
{
public:
    int numDistinct(string S, string T){
		int n = S.size();
		int m = T.size();
		
		if(n < m)
			return 0;
		
		// if(!m)
			// return pow(2, n);
		
		vector<vector<int> > M(2, vector<int>(n+1, 0));
		
		/*
			M[i,j]: T(0..i) ==> S(0..j)
			if(i>j)
				M[i,j] = 0;
			if(T[i] == S[j])
				M[i,j] = M[i-1, j-1] + M[i, j-1];
			if(T[i] != S[j])
				M[i,j] = M[i, j-1];
		*/
		int flag = 1;
		
		for(int i=0; i<=n; ++i)
			M[0][i] = 1;
			
		for(int i=1; i<=m; ++i){
			for(int j=0; j<i; ++j)
				M[flag][j] = 0;
			for(int j=i; j<=n; ++j){
				if(T[i-1] == S[j-1])
					M[flag][j] = M[!flag][j-1] + M[flag][j-1];
				else
					M[flag][j] = M[flag][j-1];
			}
			flag = !flag;
		}
		return M[!flag][n];
	}
};
 
 
 

class Solution
{
public:
	int numDistinct(string S, string T)
	{
		int m = S.size();
		int n = T.size();
		vector<vector<int> > vtrMatrix(m, vector<int>(n, numeric_limits<int>::min()));
		
		return calculateMatrix(m-1, n-1, S, T, vtrMatrix);
	}

	int calculateMatrix(int i, int j, const string &S, const string &T, vector<vector<int> > &matrix)
	{
		if(j < 0)
			return 1;
		if(i < j)
			return 0;
		if(matrix[i][j] > numeric_limits<int>::min())
			return matrix[i][j];
		
		if(S[i] == T[j])
			matrix[i][j] = calculateMatrix(i-1, j-1, S, T, matrix) + calculateMatrix(i-1, j, S, T, matrix);
		else 
			matrix[i][j] = calculateMatrix(i-1, j, S, T, matrix);
	}

};


