/**
		Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

		For example,
		Given:
		s1 = "aabcc",
		s2 = "dbbca",

		When s3 = "aadbbcbcac", return true.
		When s3 = "aadbbbaccc", return false.
		
		Analysis:
			
*/
// pass 3
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
		int m = s1.size();
		int n = s2.size();
		if(!m)
			return s2 == s3;
		if(!n)
			return s1 == s3;
		int k = s3.size();
		if(m + n != k)
			return false;
		/*
			M[i][j]: s3[0..i+j+1] is the interleaving of s1[0..i] and s2[0..j]
			M[i][j] =	true, if i==0 && j==0
						M[i][j-1] && s3[j-1]==s2[j-1], s3[0..j-1] == s2[0..j-1], if i==0
						M[i-1][j] && s3[i-1]==s1[i-1], s3[0..i-1] == s1[0..i-1], if j==0
						M[i-1][j] && s3[i+j-1]==s1[i-1]  ||  M[i][j-1] && s3[i+j-1]==s2[j-1], if i!=0 && j!=0
		*/
		vector<vector<bool> > M(m+1, vector<bool>(n+1, false));
		for(int i=0; i<=m; ++i)
			for(int j=0; j<=n; ++j)
				if(!i && !j) {
					M[i][j] = true;
				} else if(!i) {
					M[i][j] = M[i][j-1] && s3[j-1]==s2[j-1];
				} else if(!j) {
					M[i][j] = M[i-1][j] && s3[i-1]==s1[i-1];
				} else {
					M[i][j] = M[i][j-1] && s3[i+j-1]==s2[j-1] || M[i-1][j] && s3[i+j-1]==s1[i-1];
				}
		return M[m][n];
    }
};









































// Pass 2
// DP: O(|s1| * |s2|)
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
		if(s1.empty())
			return s2 == s3;
		if(s2.empty())
			return s1 == s3;
	
		int m = s1.size()+1;
		int n = s2. size()+1;
		int o = s3.size();
		if(m+n-2 != o)
			return false;
		
		vector<vector<bool> > matrix(m, vector<bool>(n, false));
		matrix[0][0] = true;
		for(int i=1; i<m; ++i)
			matrix[i][0] = matrix[i-1][0] && s3[i-1]==s1[i-1];
		for(int i=1; i<n; ++i)
			matrix[0][i] = matrix[0][i-1] && s3[i-1]==s2[i-1];
		
		for(int i=1; i<m; ++i)
			for(int j=1; j<n; ++j)
				matrix[i][j] = matrix[i-1][j]&& (s1[i-1]==s3[i+j-1]) || matrix[i][j-1]&&(s2[j-1]==s3[i+j-1]);
		return matrix[m-1][n-1];
    }
};




// Recursion version
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3){
		if(s1.empty())
			return s2 == s3;
		if(s2.empty())
			return s1 == s3;
	
		int m = s1.size();
		int n = s2. size();
		int o = s3.size();
		if(m+n != o)
			return false;
			
		return isInterleave(s1, 0, s2, 0, s3, 0);
	}
	
    bool isInterleave(const string &s1, int i, const string &s2, int j, const string &s3, int k){
		// if(i+j != k)
			// return false;
		if(i>=s1.size() && j>=s2.size() && k>=s3.size())
			return true;
		
		if(i<s1.size() && k<s3.size() && s1[i]==s3[k] && isInterleave(s1, i+1, s2, j, s3, k+1))
			return true;
			
		if(j<s2.size() && k<s3.size() && s2[j]==s3[k] && isInterleave(s1, i, s2, j+1, s3, k+1))
			return true;
			
		return false;
	}
};



// Recursion version
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3){
		if(s1.empty())
			return s2 == s3;
		if(s2.empty())
			return s1 == s3;
	
		int m = s1.size();
		int n = s2. size();
		int o = s3.size();
		if(m+n != o)
			return false;
			
		return isInterleave(s1, m-1, s2, n-1, s3, o-1);
	}
	
    bool isInterleave(const string &s1, int i, const string &s2, int j, const string &s3, int k){
		// if(i+j != k)
			// return false;
		if(i<0 && j<0 && k<0)
			return true;
		
		if(i>=0 && k>=0 && s1[i]==s3[k] && isInterleave(s1, i-1, s2, j, s3, k-1))
			return true;
			
		if(j>=0 && k>=0 && s2[j]==s3[k] && isInterleave(s1, i, s2, j-1, s3, k-1))
			return true;
			
		return false;
	}
};



























class Solution
{
public:
	// O(|s1| * |s2|)
	bool isInterleave(string s1, string s2, string s3)
	{
		if(s1.size() + s2.size() != s3.size()) 
			return false;

		vector<vector<bool> > match(s1.size()+1, vector<bool>(s2.size()+1, false));

		match[0][0] = true;
		for(int i = 0; i < s1.size() && s1[i] == s3[i]; i++)
			match[i+1][0] = true;
		for(int j = 0; j < s2.size() && s2[j] == s3[j]; j++)
			match[0][j+1] = true;

		for(int i = 0; i < s1.size(); i++) {
			for(int j = 0; j < s2.size(); j++) {
				if(s1[i] == s3[i+j+1])
					match[i+1][j+1] = match[i][j+1] || match[i+1][j+1];
				if(s2[j] == s3[i+j+1])
					match[i+1][j+1] = match[i+1][j] || match[i+1][j+1];
			}
		}
		return match[s1.size()][s2.size()];
	}
};



// Recursive: O(|s1|*|s2|)
class Solution
{
public:
	bool isInterleave(string s1, string s2, string s3)
	{
		if(s1.empty())
			return s2==s3;
			
		if(s2.empty())
			return s1==s3;
		
		if(s3.empty())
			return s1.empty() && s2.empty();
			
		char ch1 = s1[s1.size()-1];
		char ch2 = s2[s2.size()-1];
		char ch3 = s3[s3.size()-1];
		
		if(ch3 == ch1 && isInterleave(s1.substr(0, s1.size()-1), s2, s3.substr(0, s3.size()-1)))
			return true;
		if(ch3 == ch2 && isInterleave(s1, s2.substr(0, s2.size()-1), s3.substr(0, s3.size()-1)))
			return true;
			
		return false;
	}
};

