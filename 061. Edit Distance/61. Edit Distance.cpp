/**
	Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
	You have the following 3 operations permitted on a word:
	a) Insert a character
	b) Delete a character
	c) Replace a character
*/
// pass 3
class Solution {
public:
    int minDistance(string word1, string word2) {
    	int m = word1.size();
		int n = word2.size();
		if(!m)
			return n;
		if(!n)
			return m;
		
		/*
			M[i][j]: minimum steps to convert word1[0..i-1]==>word2[0..j-1]
			M[i][j]	= 	0,if i==0 && j==0
						j, if i==0
						i, if j==0
						M[i-1][j-1], if word1[i]==word1[j]
						min: 
							M[i-1][j] + 1
							M[i][j-1] + 1
							M[i-1][j-1] + 1
		*/
		vector<vector<int> > M(2, vector<int>(n+1, 0));
		for(int i=0; i<=n; ++i)
			M[0][i] = i;
		int flag = 1;
		for(int i=1; i<=m; ++i) {
			M[flag][0] = i;
			for(int j=1; j<=n; ++j)
				if(word1[i-1] == word2[j-1]) {
					M[flag][j] = M[!flag][j-1];
				} else {
					M[flag][j] = M[!flag][j] + 1;
					M[flag][j] = min(M[flag][j], M[flag][j-1] + 1);
					M[flag][j] = min(M[flag][j], M[!flag][j-1] + 1);
				}
			flag = !flag;
		}
		return M[!flag][n];
		
    }
};
















































// pass 2
class Solution {
public:
    int minDistance(string word1, string word2) {
		int m = word1.size();
		if(!m)
			return word2.size();
		int n = word2.size();
		if(!n)
			return m;
		
		vector<vector<int> > matrix(m+1, vector<int>(n+1, 0));
		/*
			M[i, j] =	j if i==0
						i if j==0
						M[i-1, j-1], if word1[i]==word2[j]
						min:
							M[i-1, j]+1, delete a word from word1, and convert word1' to word2
							M[i, j-1]+1, convert word1=>word2' and insert word2[j]
							M[i-1, j-1]+1, convert word1[i]to word2[j]
			
		*/
		for(int i=0; i<=m; ++i)
			matrix[i][0] = i;
		for(int i=0; i<=n; ++i)
			matrix[0][i] = i;
			
		for(int i=1; i<=m; ++i)
			for(int j=1; j<=n; ++j)
			{
				if(word1[i-1] == word2[j-1])
					matrix[i][j] = matrix[i-1][j-1];
				else
				{
					int minVal = min(matrix[i-1][j]+1, matrix[i][j-1]+1);
					minVal = min(minVal, matrix[i-1][j-1]+1);
					matrix[i][j] = minVal;
				}
			}
			
		return matrix[m][n];
	}
};












































#include <string>
#include <iostream>
#include <vector>
using namespace std;



class Solution {
	static int	MAXINFI;
public:
    int minDistance(string word1, string word2);
    int minDistance2(string word1, string word2);
	
private:
	int minDistance(string word1, string word2, int i, int j, vector<vector<int> >& matrix);
};

int	Solution::MAXINFI = 999999;


/**
	Recursive:
		M[i][j]: word1[0..i]==>word2[0..j]
		
		M[i][j] = 	j if i==0, insert j characters
					i if j==0, delete i characters
					M[i-1][j-1] if word1[i]==word2[j]
					min{
							M[i-1][j]+1, delete one from word1
							M[i-1][j-1]+1, convert word1[i]to word2[j]
							M[i][j-1]+1, insert word2[j] 
						} if word1[i]!=word2[j]
 */
int Solution::minDistance(string word1, string word2)
{
	int m = word1.size();
	int n = word2.size();
	
	if(!m)
		return n;
	if(!n)
		return m;
		
	vector<vector<int> > matrix(m, vector<int>(n, MAXINFI));
	int cnt = minDistance(word1, word2, m-1, n-1, matrix);
	return cnt;
}

int Solution::minDistance(string word1, string word2, int i, int j,vector<vector<int> >& matrix)
{
	if(i<0 && j<0)
		return 0;
		
	if(i<0)
		return j+1;
	else if(j<0)
		return i+1;

	if(matrix[i][j] < MAXINFI)
		return matrix[i][j];

	if(word1[i] == word2[j])
	{
		int num = minDistance(word1, word2, i-1, j-1, matrix);
		matrix[i][j] = num;
	}
	else 
	{
		int nMin = MAXINFI;
		int n1 = minDistance(word1, word2, i-1, j, matrix) + 1; //delete one from word1
		nMin = min(nMin, n1);
		
		int n2 = minDistance(word1, word2, i-1, j-1, matrix) + 1; // convert word1[i]to word2[j]
		nMin = min(nMin, n2);
		
		int n3 = minDistance(word1, word2, i, j-1, matrix) + 1; // insert word2[j] 
		nMin = min(nMin, n3);
		
		matrix[i][j] = nMin;
	}
		
	return matrix[i][j];	
}


/**
	Non-recursive method
		M[i][j]: word1[0..i]==>word2[0..j]
		
		M[i][j] = 	j if i==0, insert j characters
					i if j==0, delete i characters
					M[i-1][j-1] if word1[i]==word2[j]
					min{
							M[i-1][j]+1, delete one from word1
							M[i-1][j-1]+1, convert word1[i]to word2[j]
							M[i][j-1]+1, insert word2[j] 
						} if word1[i]!=word2[j]
*/
int Solution::minDistance2(string word1, string word2)
{
	int m = word1.size();
	int n = word2.size();
	
	if(!m)
		return n;
	if(!n)
		return m;
		
	vector<vector<int> > matrix(m+1, vector<int>(n+1, 0));
	for(int i=0; i<=m; ++i)
		matrix[i][0] = i;
	for(int i=0; i<=n; ++i)
		matrix[0][i] = i;
		
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=n; ++j)
		{
			if(word1[i-1] == word2[j-1])
				matrix[i][j] = matrix[i-1][j-1];
			else
			{
				int minVal = min(matrix[i-1][j], matrix[i-1][j-1]);
				minVal = min(minVal, matrix[i][j-1]);
				matrix[i][j] = minVal + 1;
			}
		}
		
	return matrix[m][n];
}



int main(int argc, char **argv)
{
	string word1 = "a";
	string word2 = "ab";
	
	Solution sol;
	int cnt = sol.minDistance(word1, word2);
	cout << "cnt == " << cnt << "\n";
}

