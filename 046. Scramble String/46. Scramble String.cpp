#include <iostream>
#include <string>
using namespace std;

/**
		Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

		Below is one possible representation of s1 = "great":

			great
		   /    \
		  gr    eat
		 / \    /  \
		g   r  e   at
				   / \
				  a   t
		To scramble the string, we may choose any non-leaf node and swap its two children.

		For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

			rgeat
		   /    \
		  rg    eat
		 / \    /  \
		r   g  e   at
				   / \
				  a   t
		We say that "rgeat" is a scrambled string of "great".

		Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

			rgtae
		   /    \
		  rg    tae
		 / \    /  \
		r   g  ta  e
			   / \
			  t   a
		We say that "rgtae" is a scrambled string of "great".

		Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
		
		


*/
// pass 3
class Solution {
public:
    bool isScramble(string s1, string s2) {
		string ss1 = s1;
		string ss2 = s2;
		sort(ss1.begin(), ss1.end());
		sort(ss2.begin(), ss2.end());
		if(ss1 != ss2)
			return false;
		int n = s1.size();
		if(!n)
			return true;
		
		/*
			M[i][len][j] : s1[i..i+len] and s2[j..j+len] are scramble to each other
			M[i][len][j]	=	s1[i]==s2[j], if len==0
								true; if exists m, 0<=m<len, M[i][m][j]&&M[i+m+1][len-m-1][j+m+1] || M[i][m][j+len-m]&&M[i+m+1][len-m-1][j]
		*/
		vector<vector<vector<bool> > > M(n, vector<vector<bool> >(n, vector<bool>(n, false)));
		for(int len=0; len<n; ++len)
			for(int i=0; i<n-len; ++i)
				for(int j=0; j<n-len; ++j) {
					if(!len) {
						M[i][len][j] = s1[i]==s2[j];
					}
					else {
						M[i][len][j] = false;
						for(int m=0; m<len; ++m)
							if(M[i][m][j]&&M[i+m+1][len-m-1][j+m+1] || M[i][m][j+len-m]&&M[i+m+1][len-m-1][j]) {
								M[i][len][j] = true;
								break;
							}
								
					}
				}
		return M[0][n-1][0];
    }
};
























/*
		Analysis:
			A1: s1和s2是scramble的话，那么必然存在一个在s1上的长度l1，将s1分成s11和s12两段，同样有s21和s22。
			那么要么s11和s21是scramble的并且s12和s22是scramble的；
			要么s11和s22是scramble的并且s12和s21是scramble的。
			先用递归写了一个算法，但是大集合不过，然后用三维动态规划才搞定。
			
			A2: http://www.mitbbs.com/article_t/JobHunting/32114513.html
			A3: 首先想到的是递归，简单明了，对两个string进行partition，然后比较四个字符串段。但是递归的话，这个时间复杂度比较高。然后想到能否DP，但是即使用DP的话，也要O(n^3)。想想算了，还是在递归里做些剪枝，这样就可以避免冗余计算：
			对于每两个要比较的partition，统计他们字符出现次数，如果不相等返回。
*/
// pass 3
class Solution {
public:
    bool isScramble(string s1, string s2) {
		if(s1 == s2)
			return true;
			
		string t1 = s1;
		string t2 = s2;
		sort(t1.begin(), t1.end()); // n lg n
		sort(t2.begin(), t2.end()); // n lg n
		if(t1 != t2)
			return false;
		
		int n = s1.size();
		/* 
			matrix M[i][len][k]: s1[i..i+len)] and s2[k..k+(len+1)] are scramble to each other, len = 0, 1, 2, ... , n-1
			M[i][len-1][k] =	s1[i]==s2[k], if len == 1
							if there is exists m, 1<=m<len, M[i][m-1][k]&&M[i+m][len-m-1][k+m] || M[i][m-1][k+len-m]&&M[i+m][len-m-1][k]
		*/
		vector<vector<vector<bool> > > M(n, vector<vector<bool> >(n, vector<bool>(n, false)));
		for(int len=1; len<=n; ++len)
			for(int i=0; i<=n-len; ++i)
				for(int k=0; k<=n-len; ++k)
					if(len == 1)
						M[i][len-1][k] = s1[i]==s2[k];
					else {
						M[i][len-1][k] = false;
						for(int m=1; m<len; ++m)
							if(M[i][m-1][k]&&M[i+m][len-m-1][k+m] || M[i][m-1][k+len-m]&&M[i+m][len-m-1][k])
								M[i][len-1][k] = true;
					}
		
		return M[0][n-1][0];
	}
};

// Time: exponantional 
// Space: n log n
class Solution {
public:
    bool isScramble(string s1, string s2) {
		if(s1 == s2)
			return true;
			
		string t1 = s1;
		string t2 = s2;
		sort(t1.begin(), t1.end());
		sort(t2.begin(), t2.end());
		if(t1 != t2)
			return false;
		
		for(int i=0; i<s1.size()-1; ++i) {
			string s11 = s1.substr(0, i+1);
			string s12 = s1.substr(i+1, s1.size()-i-1);
			
			string s21 = s2.substr(0, i+1);
			string s22 = s2.substr(i+1, s1.size()-i-1);
			
			if(isScramble(s11, s21) && isScramble(s12, s22))
				return true;
			
			string s32 = s2.substr(0, s2.size()-i-1);
			string s31 = s2.substr(s2.size()-i-1, i+1);
			
			if(isScramble(s11, s31) && isScramble(s12, s32))
				return true;
		}
		
		return false;
    }
};



// Space: O(n^3), time: O(n^4)
public class Solution {
    public boolean isScramble(String s1, String s2) {
		if(s1 == s2)
			return true;
		if(s1.length() != s2.length())
			return false;
			
		int n = s1.length();
		if(n == 0)
			return true;
		else if(n == 1)
			return s1.charAt(0) == s2.charAt(0);
			
		/* 
			matrix M[i][len][k]: s1[i..i+len)] and s2[k..k+(len+1)] are scramble to each other, len = 0, 1, 2, ... , n-1
			M[i][len-1][k] =	s1[i]==s2[k], if len == 1
								true, if there is exists m, 1<=m<len, M[i][m-1][k]&&M[i+m][len-m-1][k+m] || M[i][m-1][k+len-m]&&M[i+m][len-m-1][k]
		*/
		boolean[][][] M = new boolean[n][n][n];
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				for(int k=0; k<n; ++k)
					M[i][j][k] = false;

		for(int len=1; len<=n; ++len)
			for(int i=0; i<=n-len; ++i)
				for(int k=0; k<=n-len; ++k)
					if(len == 1)
						M[i][len-1][k] = s1.charAt(i)==s2.charAt(k);
					else {
						M[i][len-1][k] = false;
						for(int m=1; m<len; ++m)
							if(M[i][m-1][k]&&M[i+m][len-m-1][k+m] || M[i][m-1][k+len-m]&&M[i+m][len-m-1][k])
								M[i][len-1][k] = true;
					}
		
		return M[0][n-1][0];
	}
}
































// Pass 2
// 1. DP version
// Space: O(n^3), time: O(n^4)
class Solution {
public:
    bool isScramble(string s1, string s2) {
		int m = s1.size();
		int n = s2.size();
		if(m != n)
			return false;
		if(!n)
			return true;
		if(n==1)
			return s1 == s2;
			
		string ss1 = s1;
		string ss2 = s2;
		sort(ss1.begin(), ss1.end());
		sort(ss2.begin(), ss2.end());
		if(ss1 != ss2)
			return false;
		
		// s1[i..j] and s2[k..k+(j-i)] 
		vector<vector<vector<bool> > > M(n, vector<vector<bool> >(n, vector<bool>(n, false)));
		
		// O(n^2)
		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j)
				M[i][0][j] = s1[i]==s2[j];

		// O(n^4)
		for(int len=1; len<n; ++len)
			for(int i=0; i<n-len; ++i)
				for(int j=0; j<n-len; ++j){
					// [i..i+len] <==> [j..j+len]
					string ss1 = s1.substr(i, len+1);
					string ss2 = s2.substr(j, len+1);
					if(ss1 == ss2){
						M[i][len][j] = true;
						continue;
					}
					sort(ss1.begin(), ss1.end());
					sort(ss2.begin(), ss2.end());
					if(ss1 != ss2)
						M[i][len][j] = false;
					else{
						// [i .. i+len] <==> [j .. j+len]
						for(int pos_i=i; pos_i<i+len; ++pos_i){
							int len1 = pos_i-i+1;
							int len2 = len+1 - len1;
							
							M[i][len][j] = 	M[i][len1-1][j]&&M[i+len1][len2-1][j+len1]
											|| M[i][len2-1][j+len1]&&M[i+len2][len1-1][j];
							if(M[i][len][j])
								break;
						}
					}
				}
			
		return M[0][n-1][0];
	}
};

// 2. recursion version. 
class Solution {
public:
    bool isScramble(string s1, string s2) {
    	int m = s1.size();
		int n = s2.size();
		if(m != n)
			return false;
		if(!m)
			return true;
		if(m==1)
			return s1[0]==s2[0];
		return isScramble(s1, 0, m-1, s2, 0, n-1);
    }
	
    bool isScramble(const string &s1, const int left1, const int right1, const string &s2, const int left2, const int right2) {
		if(right1-left1+1 != right2-left2+1)
			return false;
		bool bEqual = true;
		
		int length = right1-left1+1;
		if(length == 1)
			return s1[left1]==s2[left2];
	
		string ts1 = s1.substr(left1, length),ts2 = s2.substr(left2, length);
		sort(ts1.begin(), ts1.end());
		sort(ts2.begin(), ts2.end());
		if(ts1 != ts2)
			return false;
	
		// if equal string..
#if 0
		for(int i=0; i<length; ++i)
			if(s1[left1+i] != s2[left2+i])
				bEqual = false;
		if(bEqual)
			return bEqual;
#else
		if(s1.substr(left1, length) == s2.substr(left2, length))
			return true;
#endif
		// 
		for(int k=0; k<length-1; ++k){
			//
			string s11 = s1.substr(left1, k+1);
			string s12 = s1.substr(left1+k+1, length-k-1);
			
			string s21 = s2.substr(left2, k+1);
			string s22 = s2.substr(left2+k+1, length-k-1);
			
			if(s12+s11 == s2)
				return true;
			if(s21+s22 == s1)
				return true;
			
			if(isScramble(s1, left1, left1+k, s2, left2, left2+k) && isScramble(s1, left1+k+1, right1, s2, left2+k+1, right2))
				return true;
				
			if(isScramble(s1, left1, left1+k, s2, right2-k, right2) && isScramble(s1, left1+k+1, right1, s2, left2, right2-k-1))
				return true;
		}
		
		return false;
	}
};





































class Solution
{
public:
	bool isScramble(string s1, string s2)
	{
		// if not the same string set. return false;
		if(s1.empty() && s2.empty())
			return true;
			
		int nSize = s1.size();
		
		if(nSize != s2.size())
			return false;
		
		if(s1 == s2)
			return true;
		
		string ts1 = s1,ts2 = s2;
		sort(ts1.begin(), ts1.end());
		sort(ts2.begin(), ts2.end());
		if(ts1 != ts2)
			return false;

		for(int nLen =1; nLen<nSize; ++nLen)
		{
			// foreward
			string s11 = s1.substr(0, nLen);
			string s12 = s1.substr(nLen);
			
			string s21 = s2.substr(0, nLen);
			string s22 = s2.substr(nLen);

			
			if(s12+s11 == s2)
				return true;
			if(s21+s22 == s1)
				return true;
			
			if(isScramble(s11, s21) && isScramble(s12, s22))
				return true;
				
			// backward
			int nLen2 = nSize - nLen;
			string ss11 = s1.substr(nLen2);
			string ss12 = s1.substr(0, nLen2);
			
			if(ss11+ss12 == s2)
				return true;
			
			if(isScramble(ss11, s21) && isScramble(ss12, s22))
				return true;
		}
		
		return false;
	}
};



int main(int argc, char **argv)
{
	string s1 = "ccabcbabcbabbbbcbb";
	string s2 = "bbbbabccccbbbabcba";
	
	Solution sol;
	bool b = sol.isScramble(s1, s2);
	cout << s1 << ":" << s2 << " scramble status is " << b << "\n";
}