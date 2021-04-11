/**
		Given a string, find the length of the longest substring without repeating characters. For example, the longest substring without repeating letters for "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest substring is "b", with the length of 1.
*/
// pass 3
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    	int result =0;
		int i=0;
		int j=0;
		unordered_set<char> contains;
		int count = 0;
		while(j < s.size()) {
			if(contains.find(s[j]) == contains.end()) {
				++count;
				contains.insert(s[j]);
				++j;
				result = max(result, count);
			} else {
				// shrink
				while(i <= j) {
					contains.erase(s[i]);
					--count;
					++i;
					if(s[i-1] == s[j]) {
						break;
					}
				}
			}
		}
		return result;
    }
};









































// pass 2
// Time: O(n)
// Space: O(n)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
		int len = 0;
		unordered_set<char> buf;
		queue<char> quechars;
		for(int i=0; i<s.size(); ) {
			if(buf.find(s[i]) == buf.end()) {
				buf.insert(s[i]);
				quechars.push(s[i]);
				int buflen = buf.size();
				if(buflen > len)
					len = buflen;
				++i;
			} else {
				while(!quechars.empty()) {
					char ch = quechars.front();
					quechars.pop();
					buf.erase(ch);
					if(ch == s[i])
						break;
				}
			}
		}
		return len;
	}
};

// Time: O(n^2)
// Space: O(n)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
		int len = 0;
		for(int i=0; i<s.size(); ++i) {
			unordered_set<char> buf;
			for(int j=i; j<s.size(); ++j){
				if(buf.find(s[j]) == buf.end()) {
					buf.insert(s[j]);
					int buflen = buf.size();
					if(buflen > len)
						len = buflen;
				}
				else {
					break;
				}
			}
		}
		return len;
    }
};






































class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int n = s.size();
		if(n < 2)
			return n;
		int len = 0;
		for(int i=0; i<n; ++i) {
			set<char> buf;
			for(int j=i; j<n; ++j) {
				if(buf.find(s[j]) != buf.end()) {
					break;
				} else
					buf.insert(s[j]);
				if(len < buf.size())
					len = buf.size();
			}
		}
		return len;
	}
};


