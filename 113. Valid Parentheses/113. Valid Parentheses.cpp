/**
		Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
		The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/
// pass 3
class Solution {
public:
    bool isValid(string s) {
    	int count0=0, count1=0, count2=0;
		for(int i=0; i<s.size(); ++i) {
			int cnt0=0, cnt1=0, cnt2=0;
			switch(s[i]) {
			case '(':
				++count0;
				cnt0 = 1;
				break;
			case ')':
				--count0;
				if(count0 < 0)
					return false;
				continue;
				break;
			case '[':
				++count1;
				cnt1 = 1;
				break;
			case ']':
				--count1;
				if(count1 < 0)
					return false;
				continue;
				break;
			case '{':
				++count2;
				cnt2 = 1;
				break;
			case '}':
				--count2;
				if(count2 < 0)
					return false;
				continue;
				break;
			default:
				return false;
			}
			// 
			for(int j=i+1; j<s.size(); ++j) {
				switch(s[j]) {
				case '(':
					++cnt0;
					break;
				case ')':
					--cnt0;
					break;
				case '[':
					++cnt1;
					break;
				case ']':
					--cnt1;
					break;
				case '{':
					++cnt2;
					break;
				case '}':
					--cnt2;
					break;
				default:
					return false;
				}
				if(s[i]=='('&&!cnt0 || s[i]=='['&&!cnt1 || s[i]=='{'&&!cnt2)
					break;
			}
			if(cnt0 || cnt1 || cnt2)
				return false;
		}
		if(count0 || count1 || count2)
			return false;
		return true;
    }
};



















































// pass 2
class Solution {
public:
    bool isValid(string s) {
		int count1 = 0;
		int count2 = 0;
		int count3 = 0;
		for(int i=0; i<s.size(); ++i) {
			int cnt1 = 0;
			int cnt2 = 0;
			int cnt3 = 0;
			switch(s[i]) {
			case '(':
				++count1;
				cnt1 = 1;
				break;
			case ')':
				--count1;
				if(count1 < 0)
					return false;
				continue;
				break;
			case '[':
				++count2;
				cnt2 = 1;
				break;
			case ']':
				--count2;
				if(count2 < 0)
					return false;
				continue;
				break;
			case '{':
				++count3;
				cnt3 = 1;
				break;
			case '}':
				--count3;
				if(count3 < 0)
					return false;
				continue;
				break;
			default:
				return false;
				break;
			}
			
			for(int j=i+1; j<s.size(); ++j) {
				switch(s[j]) {
				case '(':
					++cnt1;
					break;
				case ')':
					--cnt1;
					break;
				case '[':
					++cnt2;
					break;
				case ']':
					--cnt2;
					break;
				case '{':
					++cnt3;
					break;
				case '}':
					--cnt3;
					break;
				default:
					return false;
					break;
				}
				if(s[i]=='('&&!cnt1 || s[i]=='['&&!cnt2 || s[i]=='{'&&!cnt3)
					break;
			}
			if(cnt1 || cnt2 || cnt3)
				return false;
		}
		if(count1 || count2 || count3)
			return false;
		
		return true;
    }
};



// Time: O(n)
// Space: O(n)
class Solution {
public:
    bool isValid(string s) {
		stack<char> chars;
		for(int i=0; i<s.size(); ++i) {
			if(s[i]=='(' || s[i]=='[' || s[i]=='{')
				chars.push(s[i]);
			else {
				if(chars.empty())
					return false;
				char ch = chars.top();
				switch(s[i]) {
				case ')':
					if(ch != '(')
						return false;
					break;
				case ']':
					if(ch != '[')
						return false;
					break;
				case '}':
					if(ch != '{')
						return false;
					break;
				}
				chars.pop();
			}
		}
		return chars.empty();
    }
};









































class Solution {
public:
	bool isValid(string s) {
		// 
		int ncnt1 = 0;
		int ncnt2 = 0;
		int ncnt3 = 0;
		
		for(int i=0; i<s.size(); ++i) {
			int ncount1 = 0;
			int ncount2 = 0;
			int ncount3 = 0;
			switch(s[i]) {
			case '(':
				++ncnt1;
				ncount1 = 1;
				break;
			case ')':
				--ncnt1;
				if(ncnt1 < 0 || ncnt2<0 || ncnt3<0)
					return false;
				continue;
				break;
			case '[':
				++ncnt2;
				ncount2 = 1;
				break;
			case ']':
				--ncnt2;
				if(ncnt1 < 0 || ncnt2<0 || ncnt3<0)
					return false;
				continue;
				break;
			case '{':
				++ncnt3;
				ncount3 = 1;
				break;
			case '}':
				--ncnt3;
				if(ncnt1 < 0 || ncnt2<0 || ncnt3<0)
					return false;
				continue;
				break;
			default:
				return false;
			}
			
			for(int j=i+1; j<s.size(); ++j) {
				switch(s[j]) {
				case '(':
					++ncount1;
					break;
				case ')':
					--ncount1;
					break;
				case '[':
					++ncount2;
					break;
				case ']':
					--ncount2;
					break;
				case '{':
					++ncount3;
					break;
				case '}':
					--ncount3;
					break;
				default:
					return false;
				}
				if(s[i]=='('&&!ncount1 || s[i]=='['&&!ncount2 || s[i]=='{'&&!ncount3)
					break;
			}
			if(ncount1 || ncount2 || ncount3)
				return false;
		}
		
		return true;
	}
};

