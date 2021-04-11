/**
		Implement regular expression matching with support for '.' and '*'.

		'.' Matches any single character.
		'*' Matches zero or more of the preceding element.

		The matching should cover the entire input string (not partial).

		The function prototype should be:
		bool isMatch(const char *s, const char *p)

		Some examples:
		isMatch("aa","a") ? false
		isMatch("aa","aa") ? true
		isMatch("aaa","aa") ? false
		isMatch("aa", "a*") ? true
		isMatch("aa", ".*") ? true
		isMatch("ab", ".*") ? true
		isMatch("aab", "c*a*b") ? true
*/
// pass 3
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        int n = 0;
    	if(s)
			n = strlen(s);
		int m = 0;
		const char *pattern = p;
		while(*pattern) {
			if(*(pattern+1) =='*')
				pattern += 2;
			else {
				++m;
				++pattern;
			}
		}
		if(n < m)
			return false;
		if(!n)
			return true;
		
		
		vector<vector<bool> > M(2, vector<bool> (n+1, false));
		M[0][0] = true;
		int flag = 1;
		while(*p) {
			if(*(p+1) == '*') {
				M[flag][0] = M[!flag][0];
				int i = 1;
				while(i <= n) {
					if(M[flag][i-1] && (*p=='.' || *p==s[i-1]))
						M[flag][i] = true;
					else
						M[flag][i] = M[!flag][i];
					++i;
				}
				
				p += 2;
			} else {
				M[flag][0] = false;
				int i = 1;
				while(i <= n) {
					if(*p=='.' || *p==s[i-1])
						M[flag][i] = M[!flag][i-1];
					else
						M[flag][i] = false;
					++i;
				}
				
				++p;
			}
			flag = !flag;
		}
		return M[!flag][n];
    }
};


class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        int n = 0;
    	if(s)
			n = strlen(s);
		int m = 0;
		const char *pattern = p;
		while(*pattern) {
			if(*(pattern+1) =='*')
				pattern += 2;
			else {
				++m;
				++pattern;
			}
		}
		if(n < m)
			return false;
		if(!n)
			return true;
		
		vector<vector<bool> > status(2, vector<bool>(n+1, false));
		status[0][0] = true;
		int flag = 1;
		pattern = p;
		while(*pattern) {
			char ch = *pattern;
			bool hasStar = false;
			++pattern;
			if(*pattern == '*') {
				++pattern;
				hasStar = true;
				status[flag][0] = status[!flag][0];
			} else
				status[flag][0] = false;
			if(hasStar) {
				int i = 1;
				while(i <= n) {
					// when 
					//if(i==1&&status[flag][0] || i>1)
					if(status[flag][i-1])
						while(i<=n && !status[!flag][i])
							if(ch==s[i-1] || ch=='.')
								status[flag][i++] = true;
							else break;
					while(i<=n && !status[!flag][i])
						status[flag][i++] = false;
						
					// a* can be null string, so we can inheritate the old match
					while(i<=n && status[!flag][i])
						status[flag][i++] = true;
				}
			} else {
				for(int i=1; i<=n; ++i) {
					if(ch==s[i-1] || ch=='.')
						status[flag][i] = status[!flag][i-1];
					else
						status[flag][i] = false;
				}
			}
			flag = !flag;
		}
		return status[!flag][n];
    }
};






























// pass 2
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        int n = 0;
    	if(s)
			n = strlen(s);
		int m = 0;
		const char *pattern = p;
		while(*pattern) {
			if(*(pattern+1) =='*')
				pattern += 2;
			else {
				++m;
				++pattern;
			}
		}
		if(n < m)
			return false;
		if(!n)
			return true;
		
		vector<vector<bool> > status(2, vector<bool>(n+1, false));
		status[0][0] = true;
		int flag = 1;
		pattern = p;
		while(*pattern) {
			char ch = *pattern;
			bool hasStar = false;
			++pattern;
			if(*pattern == '*') {
				++pattern;
				hasStar = true;
				status[flag][0] = status[!flag][0];
			} else
				status[flag][0] = false;
			if(hasStar) {
				int i = 1;
				while(i <= n) {
					// when 
					//if(i==1&&status[flag][0] || i>1)
					if(status[flag][i-1])
						while(i<=n && !status[!flag][i])
							if(ch==s[i-1] || ch=='.')
								status[flag][i++] = true;
							else break;
					while(i<=n && !status[!flag][i])
						status[flag][i++] = false;
						
					// a* can be null string, so we can inheritate the old match
					while(i<=n && status[!flag][i])
						status[flag][i++] = true;
				}
			} else {
				for(int i=1; i<=n; ++i) {
					if(ch==s[i-1] || ch=='.')
						status[flag][i] = status[!flag][i-1];
					else
						status[flag][i] = false;
				}
			}
			flag = !flag;
		}
		return status[!flag][n];
    }
};






































class Solution {
public:
	bool isMatch(const char *s, const char *p) {
		int m = 0;
		if(s)
			m = strlen(s);
		int n = 0;
		for(int i=0; p&&p[i];) {
			if(p[i+1]=='*')
				i += 2;
			else {
				++n;
				i += 1;
			}
		}
		if(m < n)
			return false;
		if(!m && !n)
			return true;
		vector<vector<bool> > matrix(2, vector<bool>(m+1, false));
		int flag = 1;
		matrix[0][0] = true;
		while(*p) {
			if(*(p+1)=='*') {
				matrix[flag][0] = matrix[!flag][0];
				int i=1;
				// can be null string
				while(i <= m) {
					// the beginning part
					if(i==1 && matrix[flag][0] || i>1)
						while(i<=m && !matrix[!flag][i]) {
							if(*p==s[i-1] || *p=='.')
								matrix[flag][i++] = true;
							else
								break;
						}
					while(i<=m && !matrix[!flag][i])
						matrix[flag][i++] = false;
					
					while(i<=m && matrix[!flag][i])
						matrix[flag][i++] = true;
				}
				
				p += 2;
			} else {
				matrix[flag][0] = false;
				for(int i=1; i<=m; ++i)
					if(*p==s[i-1] || *p=='.')
						matrix[flag][i] = matrix[!flag][i-1]; // diagonal
					else
						matrix[flag][i] = false;
				++p;
			}
			flag = !flag;
		}
		return matrix[!flag][m];
	}
};

