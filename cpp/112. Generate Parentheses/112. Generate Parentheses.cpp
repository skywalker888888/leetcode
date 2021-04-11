/**
		Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
		For example, given n = 3, a solution set is:
		"((()))", "(()())", "(())()", "()(())", "()()()"
*/
// pass 3
class Solution {
public:
    vector<string> generateParenthesis(int n) {
    	// A = AA
		// A = (A)
		// A = NULL
		vector<string> result;
		if(!n) {
			result.push_back(string());
		} else {
			unordered_set<string> contained;
			vector<string> res1 = generateParenthesis(n-1);
			
			// append n-1, A = (A)
			for(int j=0; j<res1.size(); ++j) {
				stringstream ss;
				ss << "(" << res1[j] << ")";
				string res = ss.str();
				if(contained.find(res) == contained.end()) {
					contained.insert(res);
					result.push_back(res);
				}
			}
			
			for(int i=1; i<n; ++i) {
				vector<string> res2 = generateParenthesis(i);
				vector<string> res3 = generateParenthesis(n-i);
				// A[n] = A[i]A[n-i]
				for(int p=0; p<res2.size(); ++p)
					for(int q=0; q<res3.size(); ++q) {
						stringstream ss;
						ss << res2[p] << res3[q];
						string res = ss.str();
						if(contained.find(res) == contained.end()) {
							contained.insert(res);
							result.push_back(res);
						}
					}
			}
		}
		
		return result;
		
    }
};

class Solution {
public:
    vector<string> generateParenthesis(int n) {
    	// A = AA
		// A = (A)
		// A = NULL
		vector<vector<string> > M(n+1);
		M[0].push_back(string());
		for(int i=1; i<=n; ++i) {
			unordered_set<string> contained;
			// append n-1, A = (A)
			for(int j=0; j<M[i-1].size(); ++j) {
				stringstream ss;
				ss << "(" << M[i-1][j] << ")";
				string res = ss.str();
				if(contained.find(res) == contained.end()) {
					contained.insert(res);
					M[i].push_back(res);
				}
			}
			
			for(int i=1; i<n; ++i) {
				// A[n] = A[i]A[n-i]
				for(int p=0; p<M[i].size(); ++p)
					for(int q=0; q<M[n-i].size(); ++q) {
						stringstream ss;
						ss << M[i][p] << M[n-i][q];
						string res = ss.str();
						if(contained.find(res) == contained.end()) {
							contained.insert(res);
							M[i].push_back(res);
						}
					}
			}
		}
		return M[n];
    }
};

















































// pass 2
class Solution {
public:
	/*
		A = ^
		A = AA
		A = (A)
	*/
    vector<string> generateParenthesis(int n) {
		vector<string> result;
		if(!n) {
			result.resize(1);
			return result;
		}
		
		map<string, int> record;
		
		vector<string> res1 = generateParenthesis(n-1);
		for(int i=0; i<res1.size(); ++i) {
			string str = "(" + res1[i] + ")";
			++record[str];
			if(record[str] < 2)
				result.push_back(str);
		}
		
		for(int i=1; i<=n/2; ++i) {
			vector<string> res2 = generateParenthesis(i);
			if(i != n-i) {
				vector<string> res3 = generateParenthesis(n-i);
				for(int m=0; m<res2.size(); ++m) {
					for(int n=0; n<res3.size(); ++n) {
						string str1 = res2[m];
						string str2 = res3[n];
						
						string str = str1 + str2;
						++record[str];
						if(record[str] < 2)
							result.push_back(str);
						
						str = str2 + str1;
						++record[str];
						if(record[str] < 2)
							result.push_back(str);
					}
				}
			} else {
				for(int m=0; m<res2.size(); ++m) {
						string str = res2[m] + res2[m];
						++record[str];
						if(record[str] < 2)
							result.push_back(str);

					for(int n=m+1; n<res2.size(); ++n) {
						string str1 = res2[m];
						string str2 = res2[n];
						
						str = str1 + str2;
						++record[str];
						if(record[str] < 2)
							result.push_back(str);
						
						str = str2 + str1;
						++record[str];
						if(record[str] < 2)
							result.push_back(str);
					}
				}
			}
		}
		
		return result;
    }
};

class Solution {
public:
	/*
		A = ^
		A = AA
		A = (A)
	*/
    vector<string> generateParenthesis(int n) {
		vector<string> result;
		if(!n){
			result.push_back("");
			return result;
		}
		else if(n == 1) {
			result.push_back("()");
			return result;
		}
		
		// generate A = (A)
		vector<string> result1 = generateParenthesis(n-1);
		for(int i=0; i<result1.size(); ++i) {
			string str1 = "(";
			str1.insert(str1.end(), result1[i].begin(), result1[i].end());
			str1.push_back(')');
			result.push_back(str1);
		}
		
		// generate A = AA
		map<string, int> record;
		for(int i=1; i<n; ++i) {
			vector<string> result1 = generateParenthesis(i);
			vector<string> result2 = generateParenthesis(n-i);
			for(int i=0; i<result1.size(); ++i) 
				for(int j=0; j<result2.size(); ++j) {
					string item = result1[i];
					item.insert(item.end(), result2[j].begin(), result2[j].end());
					++record[item];
					if(record[item] < 2)
						result.push_back(item);
				}
		}
		return result;
		
    }
};
































class Solution {
public:
	/**
		A = ^
		A = AA
		A = (A)
	*/
	vector<string> generateParenthesis(int n)
	{
		vector<string> result;
		if(!n)
			return result;
		if(n == 1) {
			result.push_back("()");
			return result;
		}
		map<string, int> record;
		// (A)
		vector<string> res0 = generateParenthesis(n-1);
		for(int i=0; i<res0.size(); ++i)
			result.push_back("(" + res0[i] + ")");
		//AA
		for(int i=1; i<n; ++i) {
			vector<string> res1 = generateParenthesis(i);
			vector<string> res2 = generateParenthesis(n-i);
			for(int m=0; m<res1.size(); ++m)
				for(int n=0; n<res2.size(); ++n) {
					string str = res1[m] + res2[n];
					++record[str];
					if(record[str] < 2)
						result.push_back(str);
				}
		}
		return result;
	}
};


