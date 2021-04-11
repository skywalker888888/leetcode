/**
		Write a function to find the longest common prefix string amongst an array of strings.
*/
// pass 3
class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
		string result;
		if(!strs.size())
			return result;
			
		int i = 0;
		while(true) {
			bool match = true;
			for(int j=0; j<strs.size(); ++j) {
				if(strs.size()<=i) {
					match = false;
					break;
				}
				if(j>0 && strs[j][i]!=strs[j-1][i]) {
					match = false;
					break;
				}
			}
			if(!match)
				break;
			result.push_back(strs[0][i]);
			++i;
		}
		
		return result;
    }
};





















































// pass 2
// Time: O(n * m)
// Space: O(m)
class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
		string result;
		if(!strs.size())
			return result;
			
		int n = 0;
		while(true) {
			bool bChoose = true;
			for(int i=0; i<strs.size(); ++i)
				if(n>=strs[i].size() || strs[i][n]!=strs[0][n]) {
					bChoose = false;
					break;
				}
			if(bChoose)
				result.push_back(strs[0][n]);
			else
				break;
			++n;
		}
		return result;
    }
};























































class Solution {
public:
	string longestCommonPrefix(vector<string> &strs) {
		string ret;
		int n = strs.size();
		if(!n)
			return string();
		if(n == 1)
			return strs[0];
			
		int len = 0;
		while(true) {
			bool bchoose = true;
			for(int i=0; i<strs.size(); ++i) {
				if(len >= strs[i].size()) {
					bchoose = false;
					break;
				}
				
				if(strs[0][len] != strs[i][len]) {
					bchoose = false;
					break;
				}
			}
			if(!bchoose)
				break;
			++len;
		}
		
		return strs[0].substr(0, len);
	}

};


