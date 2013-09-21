/**
		Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/
// pass 2
class Solution {
public:
    string longestPalindrome(string s) {
		int n = s.size();
		if(n < 2)
			return s;
		string result;
		for(int i=0; i<n; ++i) {
			// 
			int j=i, k=i;
			while(j-1>=0 && k+1<n && s[j-1]==s[k+1]) {
				--j, ++k;
			}
			if(result.size() < k-j+1)
				result = s.substr(j, k-j+1);
			// 
			j=i; k=i+1;
			if(s[j] == s[k]) {
				while(j-1>=0 && k+1<n && s[j-1]==s[k+1]) {
					--j, ++k;
				}
				if(result.size() < k-j+1)
					result = s.substr(j, k-j+1);
			}
		}
		return result;
	}
};



















































class Solution {
public:
	// DP method, can not pass big case
	string longestPalindrome(string s)
	{
		int n = s.size();
		if(n < 2)
			return s;
		
		string result;
		vector<vector<bool> > matrix(n, vector<bool>(n, false));
		for(int len=0; len<n; ++len)
			for(int i=0; i<n-len; ++i)
			{
				int j = i + len;
				if(i == j)
					matrix[i][j] = true;
				else if(s[i] == s[j])
					if(i+1 == j)
						matrix[i][j] = true;
					else
						matrix[i][j] = matrix[i+1][j-1];
				else
					matrix[i][j] = false;
				if(matrix[i][j] && (j-i+1)> result.size())
					result = s.substr(i, j-i+1);
			}
			
		return result;
	}
};





class Solution {
public:
	/**
		Additional exercise:
		Could you improve the above space complexity further and how?

		A simpler approach, O(N2) time and O(1) space:
		In fact, we could solve it in O(N2) time without any extra space.

		We observe that a palindrome mirrors around its center. Therefore, a palindrome can be expanded from its center, and there are only 2N-1 such centers.

		You might be asking why there are 2N-1 but not N centers? The reason is the center of a palindrome can be in between two letters. Such palindromes have even number of letters (such as "abba") and its center are between the two 'b's.

		Since expanding a palindrome around its center could take O(N) time, the overall complexity is O(N2).
	*/
	string longestPalindrome(string s)
	{
		int n = s.size();
		if(n < 2)
			return s;
		
		string result;
		for(int i=0; i<n-1; ++i)
		{
			string str = expandPalindrome(s, i, i);
			if(str.size() > result.size())
				result = str;
			if(s[i]==s[i+1])
			{
				str = expandPalindrome(s, i, i+1);
				if(str.size() > result.size())
					result = str;
			}
		}
			
		return result;
	}

	string	expandPalindrome(string &s, int i, int j)
	{
		int n=s.size();
		while(i>0 && j<n-1)
			if(s[i-1] == s[j+1])
				--i, ++j;
			else
				break;
		return s.substr(i, j-i+1);
	}
};



// NOTE:
// See: http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
class Solution {
public:
	// Transform S into T.
	// For example, S = "abba", T = "^#a#b#b#a#$".
	// ^ and $ signs are sentinels appended to each end to avoid bounds checking
	string preProcess(string s) {
		int n = s.length();
		if (n == 0) return "^$";
		string ret = "^";
		for (int i = 0; i < n; i++)
		ret += "#" + s.substr(i, 1);
		ret += "#$";
		return ret;
	}
	string longestPalindrome(string s) {
		string T = preProcess(s);
		int n = T.length();
		int *P = new int[n];
		int C = 0, R = 0;
		for (int i = 1; i < n-1; i++) {
			int i_mirror = 2*C-i; // equals to i' = C - (i-C)
			P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
			// Attempt to expand palindrome centered at i
			while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
				P[i]++;
			// If palindrome centered at i expand past R,
			// adjust center based on expanded palindrome.
			if (i + P[i] > R) {
				C = i;
				R = i + P[i];
			}
		}
		// Find the maximum element in P.
		int maxLen = 0;
		int centerIndex = 0;
		for (int i = 1; i < n-1; i++) {
			if (P[i] > maxLen) {
				maxLen = P[i];
				centerIndex = i;
			}
		}
		delete[] P;
		return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
	}
};




