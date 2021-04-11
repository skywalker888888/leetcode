/**
		Implement wildcard pattern matching with support for '?' and '*'.

		'?' Matches any single character.
		'*' Matches any sequence of characters (including the empty sequence).

		The matching should cover the entire input string (not partial).

		The function prototype should be:
		bool isMatch(const char *s, const char *p)

		Some examples:
		isMatch("aa","a") ? false
		isMatch("aa","aa") ? true
		isMatch("aaa","aa") ? false
		isMatch("aa", "*") ? true
		isMatch("aa", "a*") ? true
		isMatch("ab", "?*") ? true
		isMatch("aab", "c*a*b") ? false
*/
// pass 3
class Solution {
public:
    bool isMatch(const char *s, const char *p) {
    	int ptnCnt = 0;
		const char *pp = p;
		while(pp && (*pp)) {
			if(*pp != '*')
				++ptnCnt;
			++pp;
		}
		
		int strCnt = 0;
		if(s)
			strCnt = strlen(s);
		
		if(strCnt < ptnCnt)
			return false;
		
		if(!strCnt)
			return !ptnCnt;
		if(!ptnCnt)
			return strlen(p);
		
		int n = strCnt;
		vector<vector<bool> > M(2, vector<bool>(n+1, false));
		M[0][0] = true;
		int flag = 1;
		pp = p;
		while(pp && *pp) {
			if(*pp == '*') {
				int i = 0;
				while(i<=n && !M[!flag][i]) {
					M[flag][i] = false;
					++i;
				}
				while(i<=n) {
					M[flag][i] = true;
					++i;
				}
			} else {
				M[flag][0] = false;
				for(int i=1; i<=n; ++i) {
					if(*pp=='?' || *pp==s[i-1])
						M[flag][i] = M[!flag][i-1];
					else
						M[flag][i] = false;
				}
			}
			flag = !flag;
			++pp;
		}
		return M[!flag][n];
    }
};






































// pass 2
class Solution {
public:
    /*
		M[i,j] =	M[i-1,j-1], if p[i]==s[j] || p[i]=='?'
					false, if p[i]!='?' && p[i]!=s[j]
					ture after the first M[i-1,k]==true, if p[i]=='*'
	*/
    bool isMatch(const char *s, const char *p) {
		if(!s || !strlen(s))
			if(!p || !strlen(p))
				return true;
			else {
					int cnt = 0;
					for(int i=0; i<strlen(p); ++i)
						if(p[i] != '*' && p[i]!='?')
							return false;
						else if(p[i] =='?') {
							if(cnt > 1)
								return false;
							++cnt;
						}
			}
		else if(!p || !strlen(p))
			return false;

		int m = strlen(p);
		int n = strlen(s);
		// there should be more non-? non-* chars in s than in p
		int num_s = 0;
		int num_p = 0;
		for(int i=0; i<m; ++i) 
			if(p[i]!='?' && p[i]!='*')
				++num_p;
		if(num_p > n)
			return false;
		
		vector<vector<bool> > M(2, vector<bool>(n+1, false));
		int flag = 1;
		M[0][0] = true;
		for(int i=0; i<m; ++i) {
			if(p[i] == '?') {
				M[flag][0] = false;
				for(int j=1; j<=n; ++j)
					M[flag][j] = M[!flag][j-1];
			
			} else if(p[i] =='*') {
				int j=0;
				for(; j<=n; ++j) {
					if(M[!flag][j])
						break;
					else
						M[flag][j] = false;
				}
				for(; j<=n; ++j)
					M[flag][j] = true;
				
			} else {
				M[flag][0] = false;
				for(int j=1; j<=n; ++j)
					if(p[i] == s[j-1])
						M[flag][j] = M[!flag][j-1];
					else 
						M[flag][j] = false;
			}
			
			flag = !flag;
		}
		return M[!flag][n];
    }
};

























































class Solution {
public:
	// http://discuss.leetcode.com/questions/222/wildcard-matching
	bool isMatch(const char *s, const char *p) {
		if(!s || !*s)
			if(!p || !*p)
				return true;
			else {
				const char *pp = p;
				while(*pp)
					if(*(pp++) != '*')
						return false;
				return true;
			}
		else if(!p || !*p)
			return false;
		const char *pp = p;
		int m = 0;
		while(*pp) {
			if(*pp != '*')
				++m;
			++pp;
		}
		int n = strlen(s);
		if(n < m)
			return false;
		vector<vector<bool> > matrix(2, vector<bool>(n+1, false));
		matrix[0][0] = true;
		bool rownum = 1;
		while(*p) {
			if(*p == '*') {
				while(*(p+1)=='*') 
					++p;
				matrix[rownum][0] = matrix[!rownum][0];
				int i;
				for(i=1; i<=n; ++i)
					if(matrix[rownum][i-1] || matrix[!rownum][i])
						break;
					else
						matrix[rownum][i] = false;
				for(; i<=n; ++i)
					matrix[rownum][i] = true;
			} else {
				matrix[rownum][0] = false;
				for(int i=1; i<=n; ++i) {
					bool bstate = false;
					if(*p==s[i-1] || *p=='?')
						bstate = matrix[!rownum][i-1]; //diagnal
					matrix[rownum][i] = bstate;
				}
			}
			++p;
			rownum = !rownum;
		};
		return matrix[!rownum][n];
	}
};


class Solution {
public:
	// http://discuss.leetcode.com/questions/222/wildcard-matching
	bool isMatch(const char *s, const char *p)
	{
		if(!s || !*s)
			if(!p || !*p)
				return true;
			else {
				const char *pp = p;
				while(*pp)
					if(*(pp++) != '*')
						return false;
				return true;
			}
		else if(!p || !*p)
			return false;
		string ss(s);
		string pp(p);
		int m = pp.size();
		int n = ss.size();
		vector<vector<bool> > matrix(m+1, vector<bool>(n+1, false));
		matrix[0][0] = true;
		for(int i=1; i<=m; ++i) {
			char cp = pp[i-1];
			// we have pp[i]
			if(cp == '*') {
				matrix[i][0] = matrix[i-1][0];
				int j;
				for(j=1; j<=n; ++j) {
					// up and left
					bool btrue = matrix[i][j-1] || matrix[i-1][j];
					if(btrue)
						break;
					else matrix[i][j] = false;
				}
				for(; j<=n; ++j)
					matrix[i][j] = true;
			} else {
				for(int j=1; j<=n; ++j)
					if(cp==ss[j-1] || cp=='?')
						matrix[i][j] = matrix[i-1][j-1];
					else
						matrix[i][j] = false;
				matrix[i][0] = false;
			}
		}
		return matrix[m][n];
	}
};

class Solution {
public:
	bool isMatch(const char *s, const char *p) {
		if(!s)
			if(!p)
				return true;
			else {
				const char *pp = p;
				while(*pp)
					if(*pp != '*')
						return false;
				return true;
			}
		else if(!p)
			return false;

		stack<pair<int, int> > stk;
		stk.push(pair<int, int>(0, 0));
		while(!stk.empty()) {
			pair<int, int> pos = stk.top();
			stk.pop();
			
			int i = pos.first;
			int j = pos.second;
			const char *ss = s + i;
			const char *pp = p + j;
			
			if(*ss == '\0')
				if(*pp == '\0')
					return true;
				else {
					bool bIsMatch = true;
					while(*pp != '\0')
						if(*(pp++) != '*') {
							bIsMatch = false;
							break;
						}
					if(!bIsMatch)
						continue;
					return true;
				}
			else if(*pp == '\0')
				continue;
			else if(*pp == '?')
				stk.push(pair<int, int>(i+1, j+1));
			else if(*pp == '*') {
				int k = j;
				while(*(p+k) == '*')
					++k;
				if(*(p+k) == '\0')
					return true;
				int i2 = i;
				while(*(s+i2)!='\0') {
					if(*(p+k)=='?' || *(s+i2) == *(p+k))
						stk.push(pair<int, int>(i2, k));
					++i2;
				}
			}
			else if(*ss != *pp)
				continue;
			else
				stk.push(pair<int, int>(i+1, j+1));
		}
		return false;
	}
};


class Solution {
public:
	bool Solution::isMatch(const char *s, const char *p) {
		if(!s)
			if(!p)
				return true;
			else {
				const char *pp = p;
				while(*pp)
					if(*pp != '*')
						return false;
				return true;
			}
		else if(!p)
			return false;
		stack<pair<int, int> > stk;
		stk.push(pair<int, int>(0, 0));
		while(!stk.empty()) {
			pair<int, int> pos = stk.top();
			stk.pop();
			while(true) {
				const char *ss = s + pos.first;
				const char *pp = p + pos.second;
				if(*ss=='\0') {
					bool bSucceed = true;
					while(*pp != '\0') {
						if(*(pp++) != '*') {
							bSucceed = false;
							break;
						}
					}
					if(!bSucceed) break;
					return true;
				} else if(*pp == '\0') {
					break;
				} else if(*pp == '?') {
					++pos.first;
					++pos.second;
				} else if(*pp == '*') {
					stk.push(pair<int, int>(pos.first+1, pos.second));
					++pos.second;
				} else if(*pp != *ss)
					break;
				else {
					++pos.first;
					++pos.second;
				}
			}
		}
		return false;
	}
};

class Solution {
public:
	bool Solution::isMatch(const char *s, const char *p) {
		if(s && !p)
			return false;
		if(!s && p && *p=='*' && *(p+1)=='\0')
			return true;
		if(!s && !p)
			return true;
		if(s && p)
			return isMatchSub(s, 0, p, 0);
			
		return false;
	}

	bool Solution::isMatchSub(const char *s, int i, const char *p, int j) {
		const char *ss = s + i;
		const char *pp = p + j;
		if(*ss=='\0') {
			if(*pp=='\0')
				return true;
			while(*pp != '\0') {
				if(*(pp++) != '*')
					return false;
			}
			return true;
		} else if(*pp == '\0') {
			return false;
		} else if(*pp == '?') {
			return isMatchSub(s, i+1, p, j+1);
		} else if(*pp == '*') {
			bool bMatch = isMatchSub(s, i, p, j+1);
			if(bMatch)
				return true;
			else 
				return isMatchSub(s, i+1, p, j);
		} else if(*pp != *ss)
			return false;
		else
			return isMatchSub(s, i+1, p, j+1);
		return false;
	}
};



class Solution {
public:
	bool Solution::isMatch(const char *s, const char *p)
	{
		if(!s || !*s)
			if(!p || !*p)
				return true;
			else {
				const char *pp = p;
				while(*pp)
					if(*(pp++) != '*')
						return false;
				return true;
			}
		else if(!p || !*p)
			return false;
			
		const char *pp = p;
		int m = 0;
		while(*pp) {
			if(*pp != '*')
				++m;
			++pp;
		}
		int n = strlen(s);
		if(n < m)
			return false;
			
		vector<string> ptns;
		generatePatterns(p, ptns);
		
		if(!ptns.size())
			return  true;
		string ss(s);
		int sstart = 0;
		int send = ss.size();
		int pstart = 0;
		int pend = ptns.size()-1;
		if(*p != '*') {
			string& ptn = ptns[0];
			int itr = findPattern(ss, 0, ptn);
			if(itr != 0)
				return false;
			sstart += ptn.size();
			pstart = 1;
			
			if(ptns.size() == 1)
				return p[strlen(p)-1]=='*' || sstart>=send;
		}
		if(p[strlen(p)-1] != '*') {
			string& ptn = ptns[ptns.size()-1];
			send = ss.size()-ptn.size();
			if(send < sstart)
				return false;
			int n = findPattern(ss, send, ptn);
			if(n < 0)
				return false;
			pend = ptns.size() - 2;
			if(ptns.size() == 1)
				return p[0]=='*' || sstart>=send;
			else if(ptns.size() == 2)
				if(pstart > pend)
					return p[strlen(p)-1-ptn.size()]=='*';
		}
		
		// * XXX * XXX * XXXX *
		if(send <= sstart)
			return false;
		
		for(int i=pstart; i<=pend; ++i) {
			string& ptn = ptns[i];
			int n = findPattern(ss, sstart, ptn);
			if(n < 0 || n+ptn.size()>send)
				return false;
			sstart = n + ptn.size();
		}
		return true;
	}
	int Solution::findPattern(string &ss, int start, string& ptn) {
		for(; start<ss.size(); ++start) {
			int i = 0;
			for(; i<ptn.size()&&start+i<ss.size(); ++i)
				if(ptn[i]!='?' && ptn[i]!=ss[start+i])
					break;
			if(i >= ptn.size())
				return start;
		}
		return -1;
	}
	void Solution::generatePatterns(const char *p, vector<string> &ptns) {
		while(*p) {
			if(*p!='*') {
				string line;
				while(*p && *p!='*') {
					line.push_back(*p);
					++p;
				}
				ptns.push_back(line);
			} else
				++p;
		}
	}
};

